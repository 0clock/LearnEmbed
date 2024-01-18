#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>


#define SER_PORT 8888			 // 服务器端口号
#define SER_IP "192.168.122.118" // 服务器IP地址
#define SER_PORT 8888			 // 服务器端口号
#define SER_IP "192.168.122.118" // 服务器IP地址

int main(int argc, const char *argv[])
{
	// 1、创建用于连接的套接字
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	// 参数1：通信域，表明使用的是ipv4协议
	// 参数2：通信方式，使用TCP通信
	// 参数3:0表示之前已经指定协议 IPPROTO_TCP

	if (sfd == -1)
	{
		perror("socket error");
		return -1;
	}
	printf("sfd = %d\n", sfd); // 3

	// 将端口号快速重用函数
	int reuse = 1;
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
	{
		perror("setsockopt error");
		return -1;
	}
	printf("端口号快速重用成功\n");

	// 2、给当前套接字绑定IP地址和端口号
	// 2.1填充要绑定的地址信息结构体
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;				 // 通信域
	sin.sin_port = htons(SER_PORT);			 // 端口号
	sin.sin_addr.s_addr = inet_addr(SER_IP); // ip地址

	// 2.2 绑定
	if (bind(sfd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		perror("bind error");
		return -1;
	}
	printf("bind success %s %s %d\n", __FILE__, __func__, __LINE__);

	// 3、将套接字设置成监听状态
	if (listen(sfd, 128) == -1)
	{
		perror("listen error");
		return -1;
	}
	printf("listen success %s %s %d\n", __FILE__, __func__, __LINE__);

	// 4、阻塞等待客户端的链接请求
	// 4.1定义容器接收客户端的地址信息
	struct sockaddr_in cin;			 // 用于接收地址信息
	socklen_t socklen = sizeof(cin); // 用于接收地址信息的大小

	int newfd = -1;

	// 11、准备一个文件描述符容器
	fd_set readfds, tempfds;
	// 22、清空容器
	FD_ZERO(&readfds);
	// 33、将要检测的文件描述符放入集合
	FD_SET(0, &readfds);
	FD_SET(sfd, &readfds);

	// 定义一个变量存储容器中最大的文件描述符
	int maxfd = sfd;

	// 定义一个地址信息结构体数组，每一个元素对应一个客户端文件描述符
	struct sockaddr_in cin_arr[1024];

	while (1)
	{
		tempfds = readfds; // 存储一份数据

		// 使用select函数对容器中的文件描述符进行检测
		int res = select(maxfd + 1, &tempfds, NULL, NULL, NULL);
		if (res == -1)
		{
			perror("select error");
			return -1;
		}
		else if (res == 0)
		{
			printf("timeout\n");
			return -1;
		}

		// 判断是否是文件描述符触发事件
		for (int cli = 0; cli <= maxfd; cli++)
		{
			// 当遍历到不存在的文件描述符直接pass
			if (!FD_ISSET(cli, &tempfds))
			{
				continue;
			}

			// 程序执行至此，说明已经有事件产生并且解除了select的阻塞
			// 并且此时文件描述符集合中只剩下本次触发的事件对应的文件描述符
			// 判断哪个文件描述符还在集合中，如果在，就执行相关函数
			if (cli == sfd)
			{

				// 4.2 接收客户端的链接
				newfd = accept(sfd, (struct sockaddr *)&cin, &socklen);
				if (newfd == -1)
				{
					perror("accept error");
					return -1;
				}
				printf("[%s:%d]发来链接请求 %s %s %d\n",
					   inet_ntoa(cin.sin_addr), ntohs(cin.sin_port), __FILE__, __func__, __LINE__);

				// 更新地址信息结构体数组
				cin_arr[newfd] = cin;

				// 将newfd放入readfds中
				FD_SET(newfd, &readfds);

				// 更新maxfd
				if (newfd > maxfd)
				{
					maxfd = newfd;
				}
			}
			else
				// 判断0号文件描述符是否在集合中
				if (cli == 0)
				{

					// 终端输入
					char wbuf[128] = "";
					scanf("%s", wbuf);
					printf("触发了终端输入事件。。。\n");
					if (strcmp(wbuf, "quit") == 0)
					{
						goto END;
					}

					// 将消息发送给所有客户端
					for (int i = 4; i <= maxfd; i++)
					{
						sendto(i, wbuf, sizeof(wbuf), 0, (struct sockaddr *)&cin_arr[i], sizeof(cin_arr[i]));
					}
				}
				else
				{

					// 5、跟客户端进行消息通信
					char buf[128] = "";

					// 将数组清空
					bzero(buf, sizeof(buf));

					// 读取客户端发来的消息
					// int res = read(newfd, buf, sizeof(buf));
					int res = recv(cli, buf, sizeof(buf), 0);
					if (res == 0)
					{
						printf("客户端已经下线\n");
						// 关闭当前通信的套接字
						close(cli);
						// 将当前文件描述符从文件描述符集合中移除
						FD_CLR(cli, &readfds);

						// 更新maxfd
						for (int i = maxfd; i >= sfd; i--)
						{
							if (FD_ISSET(i, &readfds))
							{
								maxfd = i;
								break;
							}
						}

						continue;
					}
					printf("[%s:%d] : %s\n", inet_ntoa(cin_arr[cli].sin_addr), ntohs(cin_arr[cli].sin_port), buf);

					// 给客户端发消息
					strcat(buf, "*_*");

					// write(newfd, buf, sizeof(buf));
					send(cli, buf, sizeof(buf), 0);
					printf("发送成功\n");
				}
		}
	}

END:
	// 6、关闭套接字
	close(sfd);

	return 0;
}