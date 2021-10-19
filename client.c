#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include "sock.h"

void report(const char *msg, int terminate) {
    perror(msg);
    if (terminate) exit(-1); /* failure */
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        perror("Please specify the file name");
        exit(-1);
    }

    char *fpath = argv[1];

    /* fd for the socket */
    int sockfd = socket(AF_INET,      /* versus AF_LOCAL */
                        SOCK_STREAM,  /* reliable, bidirectional */
                        0);           /* system picks protocol (TCP) */
    if (sockfd < 0) report("socket", 1); /* terminate */

    /* get the address of the host */
    struct hostent *hptr = gethostbyname(Host); /* localhost: 127.0.0.1 */
    if (!hptr) report("gethostbyname", 1); /* is hptr NULL? */
    if (hptr->h_addrtype != AF_INET)       /* versus AF_LOCAL */
        report("bad address family", 1);

    /* connect to the server: configure server's address 1st */
    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = ((struct in_addr *) hptr->h_addr_list[0])->s_addr;
    saddr.sin_port = htons(PortNumber); /* port number in big-endian */

    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0)
        report("connect", 1);

    /* Write some stuff and read the echoes. */
    puts("Connect to server, about to write some stuff...");
    int fd = open(fpath, O_RDONLY);
    if (fd == -1) {
        perror("Open!");
        exit(-1);
    }

    ssize_t ret_in, ret_out;    /* Number of bytes returned by read() and write() */
    char buffer[BuffSize];


    printf("transfer lines to server\n");
    while ((ret_in = read(fd, &buffer, BuffSize)) > 0) {
        ret_out = write(sockfd, &buffer, (ssize_t) ret_in);
        if (ret_out != ret_in) {
            /* Write error */
            perror("write");
            exit(-1);
        }
    }
    /*Send a special line to signal the end of the file*/
    write(sockfd, "\n\r\n", 3);


    printf("outputs these lines that contain the target word,\n");
    ssize_t socket_in;
    while ((socket_in = read(sockfd, buffer, sizeof(buffer))) > 0) {
        /*1 here means standard output, that is, your terminal*/
        write(1, buffer, (ssize_t) socket_in);
        /*The special character '\0' is encountered*/
        if (buffer[socket_in - 1] == '\0')
            break;
    }

    puts("Client done, about to exit...");
    close(sockfd); /* close the connection */
    return 0;
}