#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1024

typedef int (*SEND_FUNC)(int ,char *, int);
typedef int (*RECV_FUNC)(int );
// typedef void (*READ_FROM_CLIENT_FUNC)(int);

#endif