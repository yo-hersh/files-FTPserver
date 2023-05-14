#include "../Header_Files/users.h"

int add_user(bstUsers **head)
{
    int user_name[FIELD_LEN] = {0}, password[FIELD_LEN] = {0};
    bstUsers *new_user = calloc(1, sizeof(bstUsers));
    if (!new_user)
    {
        perror("allocated new_user filed!");
        return 1;
    }

    get_from_stdin(user_name, FIELD_LEN, "please insert user name - up to 20 char");

    get_from_stdin(password, FIELD_LEN, "please insert password - up to 20 char");

    strcpy(new_user->user_name, user_name);
    strcpy(new_user->password, password);

    if (add_user_to_db_file(new_user))
    {
        // error
    }
    add_to_bstUsers(head, new_user);
    return 0;
}

void get_users_list(bstUsers *head)
{
    char buf[45] = {0};
    FILE *file;
    file = fopen(USERS_FILE, "r");

    if (!file)
    {
        printf("Error: users.csv c'ent be opening.\n");
        return 1;
    }
    while (fgets(buf, 45, file))
    {
        bstUsers *new = calloc(1, sizeof(bstUsers));
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
        add_to_bstUsers(head, new);
    }
    fclose(file);
    return NULL;
}

bool login_func(char *value, int socket_id)
{
    recv_func(socket_id, value, MAX_LEN);
    bool found = false;
    char field = strtok(value, ',');
    

    for (int i = 0; i < SIZEOF_FIELDS; i++)
    {


        /* code */
    }

    // check the value of user_name and password
    return false;
};

int add_user_to_db_file(bstUsers *new_user)
{
    FILE *file = fopen(USERS_FILE, "a+");

    if (!file)
    {
        perror_handling("error opening users file");
        return 1;
    }

    char new_line[MAX_LEN] = {0};
    sprintf(new_line, "%s,%s\n", new_user->user_name, new_user->password);
    if (fputs(&new_line, file) == EOF)
    {
        perror_handling("error writing new line to users file");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

void add_to_bstUsers(bstUsers **root, bstUsers *new)
{
    if (!*root)
    {

        (*root) = new;
        return;
    }

    if (new->user_name <= (*root)->user_name)
    {
        add_to_bstUsers(&(*root)->left, new);
    }
    else
    {
        add_to_bstUsers(&(*root)->right, new);
    }
}