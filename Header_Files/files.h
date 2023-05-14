#ifndef FILES_H
#define FILES_H
#include "utils.h"

typedef struct _BSTFiles
{
    char file_name[20];
    struct _BSTFiles *left, *right;
} BSTFiles;

BSTFiles *get_files_list();
int send_files_list(int socket_id, bstFiles *files_head);
int send_file(char *file_path, int socket_id);
int recv_file(int socket_id, char *folder_to_save_in_it);

#endif