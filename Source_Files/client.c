#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../Header_Files/files.h"
#include "../Header_Files/utils.h"

bool login(int socket_id);

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
    bool permission = false;

    while (1)
    {
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
        /*
        if (!permission)
        {
            permission = login(sockfd);
            if (!permission)
            {
                puts("no permission");

                close(sockfd);
                continue;
            }
        }*/
        RECV_OPTIONS_E OPTION;
        /* test sending file*/
        OPTION = SEND_FILE;

        send(sockfd, OPTION, sizeof(int), 0);

        send_file("../Header_Files/files.h", sockfd);
        shutdown(sockfd, SHUT_WR);
        /**/
        
        close(sockfd);
    }

    close(sockfd);
    return 0;
}

RECV_OPTIONS_E select_options()
{
}

bool login(int socket_id)
{
    char user_name[FIELD_LEN] = {0}, password[FIELD_LEN] = {0};
    char str[FIELD_LEN * 3] = {0};
    int flag = 0;
    puts("please enter user name, up to 20 characters");
    /////////////////// validation needed for ensure these no included : in the name
    fgets(user_name, FIELD_LEN, stdin);
    // clean_stdin(user_name, strlen(user_name));
    puts("please enter password, up to 20 characters");
    fgets(password, FIELD_LEN, stdin);
    // clean_stdin(password, strlen(user_name));

    flag |= BIT(LOGIN);
    send_func(socket_id, &flag, sizeof(flag));

    sprintf(str, "%s:%s", user_name, password);
    printf("%s\n", str);
    send_func(socket_id, str, strlen(str));

    bool permission = false;
    printf("%d\n", permission);

    recv_func(socket_id, (int *)&permission, sizeof(int));
    printf("%d\n", permission);
    return permission;
}