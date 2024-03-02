
#define BUFFER_SIZE WIDTH *HEIGHT * 3 // RGB图像数据大小 921600
#define DATA_SIZE 1024                // RGB图像数据大小
#define PACKET_SIZE 1024              // 每个数据包的大小
#define LEN (WIDTH * HEIGHT * 2)
// 创建服务器套接字
int server_fd;
struct sockaddr_in server_addr, client_addr;
socklen_t client_len = sizeof(client_addr);

// 创建 UDP 套接字
if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
{
    perror("socket failed");
    exit(EXIT_FAILURE);
}

// 设置服务器地址结构
memset(&server_addr, 0, sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = INADDR_ANY;
server_addr.sin_port = htons(PORT);

// 绑定套接字到端口
if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
{
    perror("bind failed");
    exit(EXIT_FAILURE);
}

printf("Waiting for incoming connections...\n");

// 缓冲区用于存储图像数据
uchar buffer[BUFFER_SIZE];
char recbuf[4] = "";

recvfrom(server_fd, recbuf, sizeof(recbuf), 0, (struct sockaddr *)&client_addr, &client_len);

// 循环捕捉并处理帧

for (;;)
{

    if (1)
    {
        ssize_t bytes_sent = sendto(server_fd, jpeg_buffer.data(), jpeg_buffer.size(), 0, (struct sockaddr *)&client_addr, client_len);
        if (bytes_sent != jpeg_buffer.size())
        {
            perror("sendto failed");
            break;
        }
        // printf("send success,size=%ld\n",jpeg_buffer.size());
        // usleep(50000); // 50毫秒
    }
}