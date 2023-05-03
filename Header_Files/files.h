#ifndef FILES_H
#define FILES_H
#include "utils.h"

typedef struct _BSTFiles
{
    char file_name[20];
    struct _BSTFiles *left, *right;
} BSTFiles;

// typedef int (*SEND_FUNC)(int socket_id, int send_len);
// typedef int (*RECV_FUNC)(int socket_id);

BSTFiles *get_files_list();

int upload_file();

int send_file(char *file_name, SEND_FUNC send_func, int socket_id);

#endif