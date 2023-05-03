#ifndef USERS_H
#define USERS_H

#include "../Header_Files/utils.h"

typedef struct _BSTUsers
{
    char user_name[20];
    char password[20];
    struct _BSTUsers *left, *right;
} BSTUsers;

typedef enum
{
    USER_NAME,
    PASSWORD,
    SIZEOF_FIELDS
} USER_E;


int add_user();
int login_func();
void get_users_list(BSTUsers *head, BSTUsers *tail);
#endif