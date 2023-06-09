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

typedef struct _bstUsers
{
    char user_name[FIELD_LEN];
    char password[FIELD_LEN];
    struct _bstUsers *left, *right;
} bstUsers;

typedef struct _bstFiles
{
    char user_name[FIELD_LEN];
    char password[FIELD_LEN];
    struct _bstFiles *left, *right;
} bstFiles;


typedef struct {
    int socket_id;
    char **users_arr;
    char **files_arr;
} conn_handler_args_t;


#define BIT(i) (1 << i)

typedef int (*SEND_FUNC)(int, char *, int, CONNECTION_OPTIONS_E);
typedef int (*RECV_FUNC)(int, char *, int, CONNECTION_OPTIONS_E);
int send_func(int socket_id, void *str, int send_len);
int recv_func(int socket_id, void *str, int str_len);
void clean_stdin(char *buf);
void perror_handling(char *msg);
void get_from_stdin(char *buf, int buf_len, char *msg);
int exit_func(int socket_id);
void add_log_message(const char *message);

#endif