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

void login(int socket_id, bool *permission, bool *client_running);

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
    bool client_running = true, permission = false;

    while (client_running)
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

        if (!permission)
        {
            login(sockfd, &permission, &client_running);
            if (!permission)
            {
                puts("no permission");

                close(sockfd);
                continue;
            }
        }

        /* test sending file*/

        send_file("../Header_Files/files.h", sockfd);
        shutdown(sockfd, SHUT_WR);
        break;
        close(sockfd);
    }

    close(sockfd);
    return 0;
}

CONNECTION_OPTIONS_E select_options()
{
}

void login(int socket_id, bool *permission, bool *client_running)
{
    char user_name[FIELD_LEN] = {0}, password[FIELD_LEN] = {0},
         str[MAX_LEN] = {0};
    int ret_value;
    puts("please enter user name, up to 20 characters");
    /////////////////// validation needed for ensure these no included : in the name
    fgets(user_name, FIELD_LEN, stdin);
    // clean_stdin(user_name, strlen(user_name));
    puts("please enter password, up to 20 characters");
    fgets(password, FIELD_LEN, stdin);
    // clean_stdin(password, strlen(user_name));

    int option = (int)LOGIN;
    ret_value = send_func(socket_id, &option, sizeof(option));
    if (ret_value < 0)
    {
        goto exit;
    }

    sprintf(str, "%s:%s", user_name, password);
    ret_value = send_func(socket_id, str, strlen(str));
    if (ret_value < 0)
    {
        goto exit;
    }
    printf("permission = %d\n", (int)*permission);

    ret_value = recv_func(socket_id, permission, sizeof(permission));
    printf("permission = %d\n", (int)*permission);
    if (ret_value < 0)
    {
        *permission = false;
        goto exit;
    }

    return;
exit:
    puts("login not finished, re-login needed");
    return;
}