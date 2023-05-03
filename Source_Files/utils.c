#include "../Header_Files/utils.h"

int send_func(int socket_id, char *str, int send_len)
{
    return send(socket_id, str, send_len, 0);
}

int recv_func(int socket_id, char *str, int str_len)
{
    return recv(socket_id, str, str_len, 0);
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