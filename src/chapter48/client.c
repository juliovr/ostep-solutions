#include "sock_lib.h"


int main(int argc, char *argv[])
{
    int sd = UDP_Open(20000);
    struct sockaddr_in addr_snd, addr_rcv;
    int rc = UDP_FillSockAddr(&addr_snd, "localhost", 10000);
    char message[BUFFER_SIZE];
    sprintf(message, "hello world");
    rc = UDP_Write(sd, &addr_snd, message, BUFFER_SIZE);
    if (rc > 0) {
        rc = UDP_Read(sd, &addr_rcv, message, BUFFER_SIZE);
        printf("message received from server = %s\n", message);
    }

    return 0;
}
