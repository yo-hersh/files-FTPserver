#ifndef USERS_H
#define USERS_H

#include "../Header_Files/utils.h"

#define USERS_FILE "./users.csv"
// typedef struct _bstUsers
// {
//     char user_name[FIELD_LEN];
//     char password[FIELD_LEN];
//     struct _bstUsers *left, *right;
// } bstUsers;

typedef enum
{
    USER_NAME,
    PASSWORD,
    SIZEOF_FIELDS
} USER_E;


int add_user();
bool login_func(char *value, int socket_id);

void get_users_list(bstUsers *head);
#endif