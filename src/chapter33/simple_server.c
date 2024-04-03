#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <netdb.h>


#define MAXLEN 1024
#define LISTENQ  1024

int main(int argc, char **argv)
{
    struct addrinfo hints, *result, *addr;
    char *port = "8000";
    int rc, sockfd;
    int optval = 1;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;        /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG | AI_NUMERICSERV;
    
    rc = getaddrinfo(NULL, port, &hints, &result);
    if (rc) {
        fprintf(stderr, "[ERROR]: getaddrinfo failed: %s\n", gai_strerror(rc));
        exit(1);
    }

    for (addr = result; addr; addr = addr->ai_next) {
        sockfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (sockfd < 0) {
            continue;
        }

        /* Eliminates "Address already in use" error from bind */
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));

        rc = bind(sockfd, addr->ai_addr, addr->ai_addrlen);
        if (rc == 0) {
            break; // Success!
        }

        rc = close(sockfd);
        if (rc < 0) {
            fprintf(stderr, "[ERROR]: close failed: %s\n", gai_strerror(rc));
            exit(1);
        }
    }

    freeaddrinfo(result);

    if (addr == NULL) {
        fprintf(stderr, "[ERROR]: Could not bind\n");
        exit(1);
    }

    rc = listen(sockfd, LISTENQ);
    if (rc < 0) {
        fprintf(stderr, "[ERROR]: listen failed: %s\n", gai_strerror(rc));
        exit(1);
    }
    
    printf("OK fd = %d\n", sockfd);

    while (1) {
        int connfd = accept(sockfd, addr->ai_addr, &addr->ai_addrlen);
        printf("connected to fd = %d\n", connfd);

        char buf[MAXLEN];
        time_t rawtime;
        struct tm *timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        snprintf(buf, MAXLEN, "Current local time and date: %s", asctime(timeinfo));


        rc = write(connfd, buf, strlen(buf));
        if (rc < 0) {
            printf("Could not write to fd = %d: %s\n", connfd, gai_strerror(errno));
        }

        printf("disconnecting fd = %d\n", connfd);
        close(connfd);
    }

    return 0;
}
