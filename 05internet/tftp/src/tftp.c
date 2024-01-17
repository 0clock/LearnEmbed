#include "tftp.h"

int tftp_send()
{
    // 1、创建用于通信的套接字文件描述符
    int cfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (cfd == -1)
    {
        perror("socket error");
        return -1;
    }

    // 输入文件名
    char filename[128];
    fgets(filename, sizeof(filename), stdin);
    filename[strlen(filename) - 1] = '\0';
    int fd_cp = -1;
    fd_cp = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);

    if (fd_cp == -1)
    {
        perror("创建文件失败:");
        return -1;
    }

    // 2、绑定（可选）
    // 3、填充服务器的地址信息结构体
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SER_PORT);
    sin.sin_addr.s_addr = inet_addr(SER_IP);

    // 向服务器发送下载请求
    char send_buf[512] = "";

    // 组装请求数据
    short *p1 = (short *)send_buf;
    *p1 = htons(1);

    char *p2 = send_buf + 2;
    strcpy(p2, &filename[0]);
    char *p3 = p2 + strlen(p2) + 1;
    strcpy(p3, "octet");
    int len = 4 + strlen(p2) + strlen(p3); // 要发送的长度

    // 向服务器发送请求
    sendto(cfd, send_buf, len, 0, (struct sockaddr *)&sin, sizeof(sin));
    char rbuf[512] = "";
    int res = 0;
    short *block_count = (short *)(send_buf + 2);
    int i=1;
    do
    {
        res = recv(cfd, rbuf, sizeof(rbuf), 0);
        if (ntohs(*((short *)rbuf)) == 5)
        {
            printf("休斯顿，我们有麻烦了：\n");
            printf("[ERROR_CODE]:%d\n", ntohs(*((short *)(rbuf + 2))));
            printf("[ERROR_MSG]:%s\n", rbuf + 4);
        }

        if (ntohs(*((short *)rbuf)) == 3)
        {
            write(fd_cp, rbuf + 4, res - 4);
            // *block_count = *((short *)(rbuf + 2));
            *block_count = htons(i++);
            *p1 = htons(4);
            sendto(cfd, send_buf, 4, 0, (struct sockaddr *)&sin, sizeof(sin));
            printf("返回了ACK\n");
        }
        
        printf("block_count=%d\n", ntohs(*block_count));
        printf("res=%d\n", res);

    } while (res == 512);

    // //5、关闭套接字
    close(cfd);
    close(fd_cp);
    return 0;
}
