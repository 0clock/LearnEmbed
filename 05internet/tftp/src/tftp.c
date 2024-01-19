#include "tftp.h"

int blocksize = DATA_SIZE;

int tftp_download()
{
    int log_fp = -1;
    log_fp = open("./log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (log_fp == -1)
    {
        perror("创建文件失败:");
        return -1;
    }

    // 1、创建用于通信的套接字文件描述符
    int cfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (cfd == -1)
    {
        perror("socket error");
        return -1;
    }

    // 输入文件名
    printf("请输入要拷贝的文件名：");
    char filename[128];
    fgets(filename, sizeof(filename), stdin);
    filename[strlen(filename) - 1] = '\0';

    // 创建文件
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
    char send_buf[516] = "";

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
    char rbuf[1024] = "";
    int res = 0;
    short *block_count = (short *)(send_buf + 2);

    char log_buf[1024] = "";

    short num = 1;

    socklen_t addrlen = sizeof(sin);

    while (1) // res == 512
    {
        bzero(rbuf, 1024);
        res = recvfrom(cfd, rbuf, sizeof(rbuf), 0, (struct sockaddr *)&sin, &addrlen);
        printf("res=%d\n", res);
        if (ntohs(*((short *)rbuf)) == 5)
        {
            printf("ERROR:\n");
            printf("[ERROR_CODE]:%d\n", ntohs(*((short *)(rbuf + 2))));
            printf("[ERROR_MSG]:%s\n", rbuf + 4);
        }
        else if (ntohs(*((short *)rbuf)) == 3)
        {
            printf("收到了数据包\n");
            // write(fd_cp, rbuf + 4, res - 4);
            if (num == ntohs(*((short *)(rbuf + 2))))
            {
                write(fd_cp, rbuf + 4, res - 4);

                // 返回ACK
                *p1 = htons(4);
                *block_count = htons(num);
                if (sendto(cfd, send_buf, 4, 0, (struct sockaddr *)&sin, sizeof(sin)) < 0)
                {
                    perror("sendto error:");
                    return -1;
                }
                write(log_fp, send_buf, 4);
                printf("返回了ACK\n");
                printf("block_count=%d\n", ntohs(*block_count));
                num++;
            }
        }

        if (res < 516)
        {
            printf("接收结束！\n");
            break;
        }
    }

    // //5、关闭套接字
    close(cfd);
    close(fd_cp);
    return 0;
}

int tftp_update()
{
    struct tftp_packet rcv_packet, snd_packet;
    // 输入文件名
    printf("请输入要上传的文件名：");
    char filename[128];
    fgets(filename, sizeof(filename), stdin);
    filename[strlen(filename) - 1] = '\0';

    int fd = -1;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open error");
        return -1;
    }

    // 1、创建用于通信的套接字文件描述符
    int cfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (cfd == -1)
    {
        perror("socket error");
        return -1;
    }

    snd_packet.cmd = htons(CMD_WRQ);
    sprintf(snd_packet.filename, "%s%c%s%c%d%c", filename, 0, "octet", 0, blocksize, 0);
    // 2、绑定（可选）
    // 3、填充服务器的地址信息结构体
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SER_PORT);
    sin.sin_addr.s_addr = inet_addr(SER_IP);
    socklen_t addrlen = sizeof(sin);
    sendto(cfd, &snd_packet, sizeof(struct tftp_packet), 0, (struct sockaddr *)&sin, addrlen);

    while (1)
    {
        
    }
    

}
