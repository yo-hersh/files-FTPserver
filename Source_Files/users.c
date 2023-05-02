#include "../Header_Files/users.h"

int add_user()
{
    int buffer[21] = {0};
    puts("please insert user name - up to 20 char");
    fgets(buffer, sizeof(buffer), stdin);
    //////// adding to a struct
    puts("please insert password - up to 20 char");
    fgets(buffer, sizeof(buffer), stdin);
    //////// adding to a struct
    return 0;
}

BSTUsers *get_users_list()
{
    return NULL;
}