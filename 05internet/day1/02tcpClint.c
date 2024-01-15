/*
 * Filename: 02tcpClint.c
 * Author: linus
 * Date: 2024-01-12
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */

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


int main(int argc, const char *argv[])
{
	// 创建套接字
	int cfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in cin;
	cin.sin_family = AF_INET;
	cin.sin_port = htons(8888);
	cin.sin_addr.s_addr = inet_addr("192.168.125.78");

	// 连接服务器
	connect(cfd, (struct sockaddr *)&cin, sizeof(cin));

	char buf[128] = "";
	while (1)
	{
		printf("请输入：");
		fgets(buf, sizeof(buf), stdin);
		buf[strlen(buf) - 1] = '\0';
		write(cfd, buf, sizeof(buf));
		printf("发送成功\n");
	}

	return 0;
}
