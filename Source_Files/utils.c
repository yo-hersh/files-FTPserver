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
    int n = recv(socket_id, str, str_len);
    if (n < 0)
    {
        perror("Server error receiving data");
    }
    return n;
}

void clean_stdin(char *buf, int len)
{
    // char buffer[MAX_LEN] = {0};
    // while (fgets(buffer, sizeof(buffer), stdin) != NULL && buffer[strlen(buffer) - 1] != '\n')
    // {
    // }
    // if (buf[len-1] && buf[len-1]!= '\n')
    if (buf[len - 1] != '\n')
    {
        while (getchar() != '\n')
            ;
    }
}

void perror_handling(char *msg)
{
    perror(msg);
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