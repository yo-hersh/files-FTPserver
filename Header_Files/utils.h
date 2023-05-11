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
    RECV_FILE,
    SEND_FILE,
    EXIT,
    SIZEOF_OPTIONS
} CONNECTION_OPTIONS_E;


#define BIT(i) (1 << i)

typedef int (*SEND_FUNC)(int, char *, int, CONNECTION_OPTIONS_E);
typedef int (*RECV_FUNC)(int, char *, int, CONNECTION_OPTIONS_E);
int send_func(int socket_id, void *str, int send_len);
int recv_func(int socket_id, void *str, int str_len);
void clean_stdin(char *buf);
void perror_handling(char *msg);
void get_from_stdin(char *buf, int buf_len, char *msg);


#endif