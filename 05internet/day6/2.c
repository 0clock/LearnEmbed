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
#include <poll.h>

int main(int argc, const char *argv[])
{
    struct pollfd pfd;

    pfd.fd=0;
    pfd.events=POLLIN;

    int num;

    struct timeval tv = {5, 0};

    while (1)
    {
        int res = poll(&pfd,1,5000);
        if (res == -1)
        {
            perror("select error");
            return -1;
        }
        else if (res == 0)
        {
            printf("time out\n");
            return -1;
        }

        if (pfd.events==POLLIN)
        {
            scanf("%d", &num);
            printf("num=%d\n", num);
        }
    }

    return 0;
}
