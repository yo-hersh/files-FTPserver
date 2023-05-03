#include "../Header_Files/files.h"

BSTFiles *get_files_list()
{
    return NULL;
    ////////////// return a header of the bstNode of all lists
}

int upload_file(GET_TO_WRITE)
{

    ///////////// upload file

    ///////////// add the file to the bstNode
    return 0;
}

int send_file(char *file_name, SEND_FUNC send_func, int socket_id)
{
    char str[MAX_LEN] = {0};
    FILE *file = fopen(file_name, "r");
    if (!file)
    {
        printf("%s, not exited", file_name);
        return 1;
    }
    int n;
    do
    {
        memset(str, 0, strlen(str));
        size_t ret_code = fread(str, sizeof *str, MAX_LEN, file);
        if (ret_code)
        {
            n = send_func(socket_id, str, ret_code);
        }
        else
        {
            n = 0;
        }
        printf("ret code = %lu, n = %d, str = %s \n", ret_code, n, str);

        // if (ret_code == MAX_LEN)
        // {
        // }
        // else
        // { // error handling
        //     if (feof(fp))
        //         printf("Error reading test.bin: unexpected end of file\n");
        //     else if (ferror(fp))
        //     {
        //         perror("Error reading test.bin");
        //     }
        // }
    } while (n > 0);

    fclose(file);
}
