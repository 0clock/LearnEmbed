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

int main(int argc, const char *argv[])
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);

    int num;

    struct timeval tv = {5, 0};

    while (1)
    {
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        int res = select(1, &readfds, NULL, NULL, &tv);
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

        if (FD_ISSET(0, &readfds))
        {
            scanf("%d", &num);
            printf("num=%d\n", num);
        }
    }

    return 0;
}
