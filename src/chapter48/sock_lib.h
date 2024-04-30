/*
Communication library using UDP.
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <assert.h>
#include <stdint.h>


#define BUFFER_SIZE 4096

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;


u16 UDP_MAX_SIZE = -1;

int UDP_Open(int port)
{
    int sd;
    if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        return -1;
    }

    struct sockaddr_in myaddr;
    memset(&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family      = AF_INET;
    myaddr.sin_port        = htons(port);
    myaddr.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(sd, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1) {
        close(sd);
        return -1;
    }

    return sd;
}

int UDP_FillSockAddr(struct sockaddr_in *addr, char *hostname, int port)
{
    memset(addr, 0, sizeof(struct sockaddr_in));
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    struct in_addr *in_addr;
    struct hostent *host_entry;
    if ((host_entry = gethostbyname(hostname)) == NULL) {
        return -1;
    }
    in_addr = (struct in_addr *)host_entry->h_addr;
    addr->sin_addr = *in_addr;

    return 0;
}

int UDP_Write(int sd, struct sockaddr_in *addr, char *buffer, int n)
{
    int addr_len = sizeof(struct sockaddr_in);
    return sendto(sd, buffer, n, 0, (struct sockaddr *)addr, addr_len);
}

int UDP_Read(int sd, struct sockaddr_in *addr, char *buffer, int n)
{
    int len = sizeof(struct sockaddr_in);
    return recvfrom(sd, buffer, n, 0, (struct sockaddr *)addr, (socklen_t *)&len);
}
