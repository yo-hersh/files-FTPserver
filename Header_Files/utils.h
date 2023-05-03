#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 1024
#define FIELD_LEN 21

typedef enum
{
    LOGIN,
    GET_FILES_LIST,
    UPLOAD_FILE,
    DOWNLOAD_FILE,
    SIZEOF_OPTIONS
} RECV_OPTIONS_E;


#define BIT(i) (1 << i)

typedef int (*SEND_FUNC)(int, char *, int, int);
typedef int (*RECV_FUNC)(int, char *, int, int);
int send_func(int socket_id, char *str, int send_len, int flag);
int recv_func(int socket_id, char *str, int str_len, int flag);
void clean_stdin(char *buf, int len);

#endif