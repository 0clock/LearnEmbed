#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <winsock2.h>
#include <pthread.h>

#define LOCAL_IP      "192.168.31.254"
#define LOCAL_PORT    ((uint16_t)10126)

#define debug(...)                                     \
						do                             \
						{                              \
							printf(__VA_ARGS__);       \
							fflush(stdout);            \
						}while(0)



int main(void)
{
	int ret = 0;
	WSADATA ws;
	SOCKET sock, newsock;
	struct sockaddr_in local;
	struct sockaddr_in client;
	int addrlen = 0;
	int nrecv   = 0;
	char buf[512];

	if(WSAStartup(MAKEWORD(2, 2), &ws) != 0)
	{
		ret = -1;
		goto __exit;
	}

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock == INVALID_SOCKET)
	{
		ret = -2;
		goto __exit;
	}

	local.sin_family = AF_INET;
	local.sin_addr.S_un.S_addr = inet_addr(LOCAL_IP);
	local.sin_port = htons(LOCAL_PORT);
	memset(local.sin_zero, 0X00, sizeof(local.sin_zero));

	if(bind(sock, (const struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR)
	{
		ret = -3;
		goto __exit;
	}

	listen(sock, 5);

	addrlen = sizeof(local);

	debug(" accept %s:%d...\r\n", LOCAL_IP, LOCAL_PORT);

	if((newsock = accept(sock, (struct sockaddr *)&client, &addrlen)) == SOCKET_ERROR)
	{
		ret = -4;
		goto __exit;
	}

	debug(" %s:%d connected\r\n", inet_ntoa(client.sin_addr), client.sin_port);

	while(1)
	{
		if((nrecv = recv(newsock, buf, sizeof(buf), 0)) <= 0)
			break;

		if(strncmp(buf, "quit", 4) == 0)
			break;

		if(send(newsock, buf, nrecv, 0) < 0)
			break;
	}

__exit:
	closesocket(sock);
	closesocket(newsock);
	return ret;
}
