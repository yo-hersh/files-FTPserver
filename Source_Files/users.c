#include "../Header_Files/users.h"

int add_user(BSTUsers *Head, BSTUsers *tail)
{
    int buffer[21] = {0};
    BSTUsers *new_user = calloc(1, sizeof(BSTUsers));
    if (!new_user)
    {
        perror("allocated new_user filed!");
        return 1;
    }

    puts("please insert user name - up to 20 char");
    fgets(buffer, sizeof(buffer), stdin);
    strcpy(new_user->user_name, buffer);

    puts("please insert password - up to 20 char");
    fgets(buffer, sizeof(buffer), stdin);
    strcpy(new_user->password, buffer);

    return 0;
}

void get_users_list(BSTUsers *head, BSTUsers *tail)
{
    char buf[45] = {0};
    FILE *file;
    file = fopen("users.csv", "r");

    if (!file)
    {
        printf("Error: users.csv c'ent be opening.\n");
        return 1;
    }

    while (fgets(buf, 45, file))
    {
        BSTUsers *new = calloc(1, sizeof(BSTUsers));
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = '\0';
        }
        char *value = strtok(buf, ",");
        for (int i = 0; i < SIZEOF_FIELDS; i++)
        {
            switch (i)
            {
            case USER_NAME:
                strcpy(new->user_name, value);
                break;
            case PASSWORD:
                strcpy(new->password, value);
                break;
            }
        }
        // add_to_bstUsers(head, tail, new);
    }
    fclose(file);
    return NULL;
}

bool login_func(){return true;};
