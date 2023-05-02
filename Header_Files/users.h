#ifndef USERS_H
#define USERS_H

#include "../Header_Files/utils.h"

typedef struct _BSTUsers
{
    char user_name[20];
    char password[20];
    struct _BSTUsers *left, *right;
} BSTUsers;

int add_user();

BSTUsers *get_users_list();
#endif