#include <time.h>
#include "../Header_Files/utils.h"

int send_func(int socket_id, void *str, int send_len)
{
    int n = send(socket_id, str, send_len, 0);
    if (n < 0)
    {
        perror("Server error sending data");
    }
    return n;
}

int recv_func(int socket_id, void *str, int str_len)
{
    int n = recv(socket_id, str, str_len, 0);
    if (n < 0)
    {
        perror("Server error receiving data");
    }
    return n;
}

void perror_handling(char *msg)
{
    perror(msg);
}

void get_from_stdin(char *buf, int buf_len, char *msg)
{
    puts(msg);
    fgets(buf, buf_len, stdin);
    int len = strlen(buf);
    if (buf[len - 1] == '\n')
    {
        buf[len - 1] = '\0';
    }
    else
    {
        clean_stdin(buf);
    }
}

void clean_stdin(char *buf)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    // buf[0] = '\0';
}

// void insert_to_bst(BSTNode *node, BSTNode **root)
// {
//     while (*root)
//     {
//         if (node->data <= (*root)->data)
//         {
//             root = &((*root)->left);
//         }
//         else
//         {
//             root = &((*root)->right);
//         }
//     }
//     *root = node;
// }

// int exit_func(int socket_id, bstUsers *users_head, bstFiles *files_head)
// {

//     return 0;
// }
int exit_func(int socket_id)
{
    return 0;
}

void add_log_message(const char *message)
{
    FILE *log_file = fopen("log_file.txt", "a");
    if (log_file == NULL)
    {
        perror("Error opening log file");
        return;
    }

    time_t raw_time;
    struct tm *time_info;
    time(&raw_time);
    time_info = localtime(&raw_time);

    fprintf(log_file, "[%02d-%02d-%d %02d:%02d:%02d] %s\n", time_info->tm_mday,
            time_info->tm_mon + 1, time_info->tm_year + 1900, time_info->tm_hour, time_info->tm_min,
            time_info->tm_sec, message);

    fclose(log_file);
}
