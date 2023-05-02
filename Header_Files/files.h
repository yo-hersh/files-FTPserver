#ifndef FILES_H
#define FILES_H
#include "utils.h"

typedef struct _BSTFiles
{
    char file_name[20];
    struct _BSTFiles *left, *right;
} BSTFiles;

BSTFiles *get_files_list();

int upload_file();

int download_file();

#endif