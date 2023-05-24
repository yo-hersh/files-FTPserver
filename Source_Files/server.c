#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <pthread.h>
#include "../Header_Files/utils.h"
#include "../Header_Files/files.h"
#include "../Header_Files/users.h"

void *conn_handler(void *args);
void mange_server(int socket_id, bool *server_running);

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr = {}, cliaddr = {};
    socklen_t len = sizeof(cliaddr);
    char buffer[MAX_LEN];
    fd_set readfds;
    int n, r;

    if (argc < 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Create a socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return EXIT_FAILURE;
    }

    /* Bind the socket to a specific port */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Error binding socket");
        return EXIT_FAILURE;
    }

    if (listen(sockfd, 1) < 0)
    {
        perror("Error listening");
        return EXIT_FAILURE;
    }

    add_log_message("Server started");

    bool server_running = true;
    char **users_arr = NULL, **files_arr = NULL;

    get_users_list(users_arr);

    conn_handler_args_t args =
        {
            .users_arr = users_arr,
            .files_arr = files_arr,
        };

    /* Receive data from clients */
    while (server_running)
    {
        // clear the socket set
        FD_ZERO(&readfds);

        // add the server socket and stdin to the set
        FD_SET(sockfd, &readfds);
        FD_SET(STDIN_FILENO, &readfds);
        if (select(sockfd + 1, &readfds, NULL, NULL, NULL) < 0)
        {
            perror("select failed");
            goto exit;
        }

        if (FD_ISSET(sockfd, &readfds))
        {
            pthread_t tid;
            int new_sock = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&len);
            if (new_sock < 0)
            {
                perror("accept failed");
                goto exit;
            }
            args.socket_id = &new_sock;

            pthread_create(&tid, NULL, conn_handler, (void *)&args);
        }
        else if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            mange_server(sockfd, &server_running);
        }
    }

    close(sockfd);
    return EXIT_SUCCESS;
exit:
    close(sockfd);
    return EXIT_FAILURE;
}

void *conn_handler(void *args)
{
    conn_handler_args_t *handler_args = (conn_handler_args_t *)args;
    int socket_id = *(int *)handler_args->socket_id;
    char **users_arr = handler_args->users_arr;
    char **files_arr = handler_args->files_arr;

    bool permission = false;

    char buffer[MAX_LEN] = {0};
    int ret_value;

    CONNECTION_OPTIONS_E OPTION;
    int option_buf;

    ret_value = recv(socket_id, &option_buf, sizeof(option_buf), 0);
    if (ret_value < 0)
    {
        perror_handling("error receiving option");
        goto exit;
    }

    OPTION = (CONNECTION_OPTIONS_E)option_buf;
    if (!permission)
    {

        if (OPTION == LOGIN)
        {
            permission = login_func(buffer, socket_id);
            if (!permission)
                goto exit;
        }
        else
        {
            printf("OOPS, client not send the login info\n");
            goto exit;
        }
        printf("permission = %d\n", (int)permission);
        ret_value = send(socket_id, &permission, sizeof(permission), 0);
        if (ret_value < 0)
        {
            perror_handling("error sending option");
            goto exit;
        }
    }

    bool client_running = true;

    while (client_running)
    {
        switch (OPTION)
        {
        case GET_FILES_LIST:
            ret_value = send_files_list(socket_id, files_arr);
            break;
        case SEND_FILE:
            ret_value = recv_file(socket_id, "../server_public_files");
            break;
        case RECV_FILE:
            ret_value = send_file_func(socket_id);
            break;
        case EXIT:
            client_running = false;
            continue;
        }
        if (ret_value)
            goto exit;

        ret_value = recv(socket_id, &option_buf, sizeof(option_buf), 0);
        if (ret_value < 0)
        {
            perror_handling("error receiving option");
            goto exit;
        }
        OPTION = (CONNECTION_OPTIONS_E)option_buf;
    }

exit:
    close(socket_id);
    return;
}

void mange_server(int socket_id, bool *server_running)
{
    char buffer[MAX_LEN] = {0};
    fgets(buffer, sizeof(buffer), stdin);
    if (!strncmp(buffer, "exit", 4))
    {
        *server_running = false;
        return;
    }
    if (!strncmp(buffer, "add user", 8))
    {
        int res = add_user();
        if (res)
        {
            puts("creation feild");
        }
        else
        {
            puts("created successfully");
        }
    }
}
