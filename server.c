#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "sock.h"
#include "read_line.h"

void report(const char *msg, int terminate) {
    perror(msg);
    if (terminate) exit(-1); /* failure */
}

int containWordIgnoreCase(char *line, char *word, int n) {
    int m = strlen(word);

    char *lower_line = calloc(n+1, sizeof(char));
    for (size_t i = 0; i < n; ++i) {
       lower_line[i] = tolower((unsigned char)line[i]);
    }
    char *lower_word = calloc(m+1, sizeof(char));
    for (size_t i = 0; i < m; ++i) {
       lower_word[i] = tolower((unsigned char)word[i]);
    } 

    char * ret = strstr (lower_line, lower_word); 

    int return_val  = 0;
    if ( ret != NULL )
        if ( strlen(ret)==m || !isalnum(ret[m]))
        {
              if( ret != lower_line )
                 {ret--;
                 if (!isalnum(ret[0]))
		      return_val = 1;
                 }
        }
    free(lower_line);
    free(lower_word);

    return return_val;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        perror("Please specify the target word");
        exit(-1);
    }
    char *target = argv[1];

    int fd = socket(AF_INET,     /* network versus AF_LOCAL */
                    SOCK_STREAM, /* reliable, bidirectional, arbitrary payload size */
                    0);          /* system picks underlying protocol (TCP) */
    if (fd < 0) report("socket", 1); /* terminate */

    /* bind the server's local address in memory */
    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof(saddr));          /* clear the bytes */
    saddr.sin_family = AF_INET;                /* versus AF_LOCAL */
    saddr.sin_addr.s_addr = htonl(INADDR_ANY); /* host-to-network endian */
    saddr.sin_port = htons(PortNumber);        /* for listening */

    if (bind(fd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0)
        report("bind", 1); /* terminate */

    /* listen to the socket */
    if (listen(fd, MaxConnects) < 0) /* listen for clients, up to MaxConnects */
        report("listen", 1); /* terminate */

    fprintf(stderr, "Listening on port %i for clients...\n", PortNumber);
    /* a server traditionally listens indefinitely */
    while (1) {
        struct sockaddr_in caddr; /* client address */
        int len = sizeof(caddr);  /* address length could change */

        int client_fd = accept(fd, (struct sockaddr *) &caddr, &len);  /* accept blocks */
        if (client_fd < 0) {
            report("accept", 0); /* don't terminate, though there's a problem */
            continue;
        }
        printf("connection linked\n");

        /* read from client */
        ssize_t socket_in;
        char buffer[BuffSize];
        FILE *fp;

        fp = fopen("./tmp.txt", "w+");
        printf("1. start read file content\n");
        while ((socket_in = readLine(client_fd, buffer, sizeof(buffer))) > 0) {
            if (containWordIgnoreCase(buffer, target, socket_in)) {
                char subbuff[socket_in + 1];
                memcpy(subbuff, &buffer, socket_in);
                subbuff[socket_in] = '\0';
                // write(1, buffer, (ssize_t) socket_in);
                fputs(subbuff, fp);
            }
            /*The special line '\r\n' is encountered*/
            if (buffer[0] == '\r' && buffer[1] == '\n') {
                printf("1. end read file content\n");
                break;
            }
        }
        fclose(fp);

        int tmpfd = open("./tmp.txt", O_RDONLY);
        if (tmpfd == -1) {
            perror("Open!");
            exit(-1);
        }
        ssize_t ret_in, ret_out;
        printf("2. start sends lines that contain the target word back\n");
        while ((ret_in = read(tmpfd, &buffer, BuffSize)) > 0) {
            ret_out = write(client_fd, &buffer, (ssize_t) ret_in);
            if (ret_out != ret_in) {
                /* Write error */
                perror("write");
                exit(-1);
            }
        }
        printf("2. end sends lines that contain the target word back\n");
        close(tmpfd);
        close(client_fd); /* break connection */
        printf("end close\n");
    }  /* while(1) */
    return 0;
}
