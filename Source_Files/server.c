#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <fcntl.h>

#define MAX_LEN 1024

int main(int argc, char **argv)
{
    int sockfd, new_sock;
    struct sockaddr_in servaddr = {}, cliaddr = {};
    socklen_t len = sizeof(cliaddr);
    char buffer[MAX_LEN];
    fd_set readfds;
    int n, r;

    if (argc < 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        // return 1;
    }

    /* Create a socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return 1;
    }

    // int flags = fcntl(sockfd, F_GETFL, 0);
    // fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    /* Bind the socket to a specific port */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Error binding socket");
        return 1;
    }

    if (listen(sockfd, 1) < 0)
    {
        perror("Error listenning");
        return 1;
    }

    /* Receive data from clients */
    while (1)
    {
        // clear the socket set
        FD_ZERO(&readfds);

        // add the server socket and stdin to the set
        FD_SET(sockfd, &readfds);
        FD_SET(STDIN_FILENO, &readfds);
        if (select(sockfd + 1, &readfds, NULL, NULL, NULL) < 0)
        {
            perror("select failed");
            return 1;
        }

        if (FD_ISSET(sockfd, &readfds))
        {
            new_sock = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&len);
            if (new_sock < 0)
            {
                perror("accept failed");
                return 1;
            }
            r = 0;
            do
            {
                n = recv(new_sock, buffer + r, MAX_LEN - r, 0);
                if (n < 0)
                {
                    perror("Server error receiving data");
                    return 1;
                }
                r += n;
            } while (n);
            buffer[r] = '\0';
            printf("Server received: %s\n", buffer);

            strcpy(buffer, "Thanks from TCP server!");
            n = send(new_sock, buffer, strlen(buffer), 0);
            if (n < 0)
            {
                perror("Server error sending data");
                return 1;
            }
            shutdown(new_sock, SHUT_WR);

            close(new_sock);
        }
        else if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            fgets(buffer, sizeof(buffer), stdin);
            printf("Received from stdin: %s", buffer);
            if (!strncmp(buffer, "exit", 4))
            {
                puts("Exiting...");
                break;
            }
        }
    }

    close(sockfd);

    return 0;
}