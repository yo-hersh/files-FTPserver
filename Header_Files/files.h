#ifndef FILES_H
#define FILES_H
#include "utils.h"

typedef struct _BSTNode
{
    char file_name[20];
    struct _BSTNode *left, *right;
} BSTNode;

BSTNode *get_files()
{    
    ////////////// return a header of the bstNode of all lists 
}

int upload_file()
{
    ///////////// upload file

    ///////////// add the file to the bstNode
}

int download_file()
{
    ///////////// down file

}

#endif