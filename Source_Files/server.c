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
void mange_server();

typedef struct Recv_functions
{
    RECV_OPTIONS_E OPTION;
    int (*recv_func)(char *value, int socket_id);
} Recv_functions;

Recv_functions recv_functions[] = {
    {LOGIN, login_func},
    {GET_FILES_LIST, get_files_list},
    {RECV_FILE, recv_file},
    {SEND_FILE, send_file},
};

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
        // return 1;
    }

    /* Create a socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return 1;
    }

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
        perror("Error listening");
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
            pthread_t tid;
            int new_sock = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&len);
            if (new_sock < 0)
            {
                perror("accept failed");
                return EXIT_FAILURE;
            }

            pthread_create(&tid, NULL, conn_handler, (void *)&new_sock);
        }
        else if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            mange_server();
        }
    }

    close(sockfd);

    return 0;
}

void *conn_handler(void *args)
{
    bool permission = false;

    char buffer[MAX_LEN] = {0};
    int socket_id = *((int *)args);
    int ret_value;

    RECV_OPTIONS_E OPTION;

    while (!permission)
    {
        ret_value = recv_func(socket_id, &OPTION, sizeof(OPTION));
        if (ret_value < 0)
        {
            perror_handling("error receiving option");
            goto exit;
        }
        if (OPTION == LOGIN)
        {
            permission = (bool)recv_functions[LOGIN].recv_func(buffer, socket_id);
        }
        else
        {
            printf("OOPS, client not send the login info\n");
            goto exit;
        }

        ret_value = send(socket_id, (int)permission, sizeof(permission), 0);
        if (ret_value < 0)
        {
            perror_handling("error receiving option");
            goto exit;
        }
    }

    bool client_running = true;
    while (client_running)
    {
        ret_value = recv_func(socket_id, &OPTION, sizeof(OPTION));
        if (ret_value < 0)
        {
            perror_handling("error receiving option");
            goto exit;
        }
        if (OPTION == EXIT)
        {
            client_running = false;
            continue;
        }
        recv_functions[OPTION].recv_func(buffer, socket_id);
    }

exit:
    close(socket_id);
    return;

}

void mange_server()
{
    char buffer[21] = {0};
    fgets(buffer, sizeof(buffer), stdin);
    if (!strncmp(buffer, "exit", 4))
    {
        ///////////// do something
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