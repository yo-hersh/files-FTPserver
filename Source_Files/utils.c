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
    while ((c = getchar()) != '\n' && c != EOF);
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