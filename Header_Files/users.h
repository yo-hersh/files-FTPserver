#ifndef USERS_H
#define USERS_H

#include "../Header_Files/utils.h"

#define USERS_FILE "users.csv"
typedef struct _BSTUsers
{
    char user_name[FIELD_LEN];
    char password[FIELD_LEN];
    struct _BSTUsers *left, *right;
} BSTUsers;

typedef enum
{
    USER_NAME,
    PASSWORD,
    SIZEOF_FIELDS
} USER_E;


int add_user();
bool login_func();
void get_users_list(BSTUsers *head);
#endif