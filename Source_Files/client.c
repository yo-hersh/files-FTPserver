#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../Header_Files/files.h"

#define MAX_LEN 4096

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr = {};
    char buffer[MAX_LEN];
    int n, r;

    if (argc < 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    /* Connect to the server */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(atoi(argv[1]));

    /* Send data to the server */
    while (1)
    {
        // get_options();
        printf("Enter a message: ");
        fgets(buffer, MAX_LEN, stdin);
        if (!strncmp(buffer, "exit", 4))
        {
            puts("Exiting...");
            break;
        }
        /* Create a socket */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
        {
            perror("Error creating socket");
            return 1;
        }

        /* Connect to server */
        if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
            perror("Error connecting");
            break;
        }

        n = send(sockfd, buffer, strlen(buffer) - 1, 0);
        if (n < 0)
        {
            perror("Client error sending data");
            break;
        }
        shutdown(sockfd, SHUT_WR);

        recv_file("server_copy.c", recv_func, sockfd);
        // r = 0;
        // do
        // {
        //     n = recv(sockfd, buffer + r, MAX_LEN - r, 0);
        //     r += n;
        // } while (n > 0);
        // if (n < 0)
        // {
        //     perror("Client error receiving data");
        //     break;
        // }
        // buffer[r] = '\0';
        // printf("%s\n", buffer);

        close(sockfd);
    }

    close(sockfd);
    return 0;
}