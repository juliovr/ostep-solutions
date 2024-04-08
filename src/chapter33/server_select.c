#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <netdb.h>
#include <fcntl.h>


#define MAXLEN 1024
#define LISTENQ  1024
#define FILENAME_SIZE 64
#define BUFFER_SIZE 1024


typedef struct pool_t {
    fd_set ready_set;
    fd_set read_set;
    int max_fd;
    int max_i;
    int n_ready;
    int clientfd[FD_SETSIZE];
} pool_t;


static pool_t pool;


void init_pool(pool_t *pool, int sockfd)
{
    FD_ZERO(&pool->read_set);
    FD_SET(sockfd, &pool->read_set);

    pool->max_fd = sockfd;
    pool->max_i = 0;
    for (int i = 0; i < FD_SETSIZE; i++) {
        pool->clientfd[i] = -1;
    }
}

void add_client(pool_t *pool, int connfd)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (pool->clientfd[i] < 0) { /* Available slot */
            pool->clientfd[i] = connfd;
            FD_SET(connfd, &pool->read_set);

            if (i > pool->max_i) {
                pool->max_i = i;
            }

            if (connfd > pool->max_fd) {
                pool->max_fd = connfd;
            }

            // Welcome message
            char buf[MAXLEN];
            time_t rawtime;
            struct tm *timeinfo;            

            printf("connected to fd = %d\n", connfd);

            time(&rawtime);
            timeinfo = localtime(&rawtime);
            snprintf(buf, MAXLEN, "Current local time and date: %s", asctime(timeinfo));

            if (write(connfd, buf, strlen(buf)) < 0) {
                printf("Could not write to fd = %d: %s\n", connfd, gai_strerror(errno));
            }


            break;
        }
    }
}

void replace_line_feed(char *string, int size)
{
    for (int i = 0; i < size; i++) {
        if (string[i] == '\r' || string[i] == '\n') {
            string[i] = 0;
            break;
        }
    }
}

void process_clients(pool_t *pool)
{
    if (pool->n_ready < 0) {
        return;
    }

    char filename[FILENAME_SIZE] = {};
    char buffer[BUFFER_SIZE] = {};
    
    for (int i = 0; i <= pool->max_i; i++) {
        int connfd = pool->clientfd[i];
        if (connfd < 0) {
            continue;
        }

        if (FD_ISSET(connfd, &pool->ready_set)) {
            pool->n_ready--;

            if (read(connfd, filename, FILENAME_SIZE) < 0) {
                printf("Could not read filename\n");
            } else {
                replace_line_feed(filename, FILENAME_SIZE);

                int filefd;
                if ((filefd = open(filename, O_RDONLY, 0)) < 0) {
                    printf("Could not open file %s: %s\n", filename, gai_strerror(errno));
                } else {
                    ssize_t bytes_read;
                    if ((bytes_read = read(filefd, buffer, BUFFER_SIZE)) < 0) {
                        printf("Could read file %s: %s\n", filename, gai_strerror(errno));
                    } else {
                        close(filefd);

                        buffer[bytes_read] = '\r';
                        buffer[bytes_read + 1] = '\n';
                        if (write(connfd, buffer, BUFFER_SIZE) < 0) {
                            printf("Could not write file to fd = %d: %s\n", connfd, gai_strerror(errno));
                        }
                    }
                }
            }


            printf("disconnecting fd = %d\n", connfd);
            close(connfd);

            FD_CLR(connfd, &pool->read_set);
            pool->clientfd[i] = -1;
        }
    }
}


int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    char *port = argv[1];
    
    /* begin: open_listenfd */
    struct addrinfo hints, *result, *addr;
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
    /* end: open_listenfd */

    
    init_pool(&pool, sockfd);

    while (1) {
        pool.ready_set = pool.read_set;

        pool.n_ready = select(pool.max_fd + 1, &pool.ready_set, NULL, NULL, NULL);
        if (FD_ISSET(sockfd, &pool.ready_set)) {
            int connfd = accept(sockfd, addr->ai_addr, &addr->ai_addrlen);

            add_client(&pool, connfd);
        }

        process_clients(&pool);
    }

    return 0;
}
