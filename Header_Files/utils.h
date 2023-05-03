#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1024

typedef int (*SEND_FUNC)(int, char *, int);
typedef int (*RECV_FUNC)(int, char *, int);
int send_func(int socket_id, char *str, int send_len);
int recv_func(int socket_id, char *str, int str_len);
void clean_stdin();

#endif