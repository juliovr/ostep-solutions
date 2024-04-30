#include "sock_lib.h"


int main(int argc, char *argv[])
{
    int sd = UDP_Open(10000);
    assert(sd > -1);

    printf("starting server...\n");

    while (1) {
        struct sockaddr_in addr;
        char message[BUFFER_SIZE];
        int rc = UDP_Read(sd, &addr, message, BUFFER_SIZE);
        printf("message received from client = %s\n", message);
        if (rc > 0) {
            char reply[BUFFER_SIZE];
            sprintf(reply, "goodbye world");
            rc = UDP_Write(sd, &addr, reply, BUFFER_SIZE);
        }
    }

    return 0;
}
