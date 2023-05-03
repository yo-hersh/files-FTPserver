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
    RECV_OPTIONS_E option;
    int (*recv_func)(char *value, int socket_id);
} Recv_functions;


Recv_functions recv_functions[] = {
    {LOGIN, login_func},
    {GET_FILES_LIST, get_files_list},
    {UPLOAD_FILE, upload_file},
    {DOWNLOAD_FILE, send_file},
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
    int flag = 0;
    while (!permission)
    {
        recv_func(socket_id, buffer, MAX_LEN, flag);
        if (flag & BIT(LOGIN))
        {
            permission = (bool)recv_functions[LOGIN].recv_func(buffer, socket_id);
        }
        send(socket_id, (int)permission, sizeof(int), 0);
        // send_func(socket_id, permission, sizeof(bool), 0);
    }

    recv_func(socket_id, buffer, MAX_LEN, flag);
    char *file_name = "server.c";
    int ret_code = 0;
    for (int i = 0; i < SIZEOF_OPTIONS; i++)
    {
        if (flag & BIT(i))
        {
            ret_code = recv_functions[i].recv_func(buffer, socket_id);
        }
    }

    int n, r = 0;
    // do
    // {
    //     n = recv(socket_id, buffer + r, MAX_LEN - r, 0);
    //     if (n < 0)
    //     {
    //         perror("Server error receiving data");
    //         return 1;
    //     }
    //     r += n;
    // } while (n);
    // buffer[r] = '\0';
    // printf("Server received: %s\n", buffer);
    send_file(file_name, send_func, socket_id);
    // write_to_file(file_name, socket_id);
    strcpy(buffer, "Thanks from TCP server!");
    // n = send(socket_id, buffer, strlen(buffer), 0);
    if (n < 0)
    {
        perror("Server error sending data");
        // return 1?;
    }
    shutdown(socket_id, SHUT_WR);

    close(socket_id);
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