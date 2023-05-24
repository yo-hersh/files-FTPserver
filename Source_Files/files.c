#include "../Header_Files/files.h"
#include <libgen.h>

void get_files_list(char **files_arr);
void get_file_name(const char *file_path, char *file_name);
int get_file_size(FILE *file);

int send_file(char *file_path, int socket_id)
{

    FILE *file = fopen(file_path, "rb");
    if (!file)
    {
        perror("error opening file");
        return EXIT_FAILURE;
    }

    char file_name[FIELD_LEN] = {0};
    get_file_name(file_path, file_name);

    int ret_value = send(socket_id, file_name, strlen(file_name), 0);
    if (ret_value < 0)
    {
        perror_handling("error sending file name");
        goto error;
    }

    int file_size = get_file_size(file);
    ret_value = send(socket_id, &file_size, sizeof(file_size), 0);
    if (ret_value < 0)
    {
        perror_handling("error sending file size");
        goto error;
    }

    int bytes_sent = 0;
    char buffer[MAX_LEN] = {0};

    int bytes_read = fread(buffer, sizeof *buffer, MAX_LEN, file);
    while (bytes_read)
    {
        bytes_sent += send_func(socket_id, buffer, bytes_read);
        if (bytes_sent < 0)
        {
            perror_handling("error sending file");
            goto error;
        }
        bytes_read = fread(buffer, sizeof *buffer, MAX_LEN, file);
    }

    printf("error: not sending all data");
    fclose(file);

    return EXIT_SUCCESS;
error:
    fclose(file);
    return EXIT_FAILURE;
}

int recv_file(int socket_id, char *folder_to_save_in_it)
{
    int file_name[FIELD_LEN] = {0};

    int ret_value = recv(socket_id, &file_name, strlen(file_name), 0);
    if (ret_value < 0)
    {
        perror_handling("error receiving file name");
        return EXIT_FAILURE;
    }

    char file_path[MAX_LEN] = {0};
    snprintf(file_path, strlen(file_path), "../%s/%s", folder_to_save_in_it, file_name);
    FILE *file = fopen(file_path, "a+");
    if (!file)
    {
        perror("error opening file");
        return EXIT_FAILURE;
    }

    int file_size = 0;
    ret_value = recv(socket_id, &file_size, sizeof(file_size), 0);
    if (ret_value < 0)
    {
        perror_handling("error receiving file size");
        goto error;
    }

    char buffer[MAX_LEN];

    while (file_size)
    {
        memset(buffer, strlen(buffer), 0);
        ret_value = recv(socket_id, buffer, sizeof(buffer), 0);
        if (ret_value < 0)
        {
            perror_handling("error receiving file data");
            goto error;
        }
        fwrite(buffer, sizeof(char), ret_value, file);

        file_size -= ret_value;
    }

    printf("receiving file %s successfully\n", file_name);
    fclose(file);
    return EXIT_SUCCESS;
error:
    fclose(file);
    return EXIT_FAILURE;
}

int get_file_size(FILE *file)
{
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

void get_file_name(const char *file_path, char *file_name)
{
    file_name = basename(file_path);
}

int send_files_list(int socket_id, char **files_arr)
{
    char buffer[MAX_LEN] = {0};

    int num_files = 0;
    while (files_arr[num_files] != NULL)
    {
        num_files++;
    }

    int ret_value;

    ret_value = send(socket_id, &num_files, sizeof(num_files), 0);
    if (ret_value < 0)
    {
        perror("send num_files failed");
        return 1;
    }

    int file_len = 0, index = 0;
    for (int i = 0; i < num_files; i++)
    {
        file_len = strlen(files_arr[i]) + 1;
        if (index + file_len < MAX_LEN)
        {
            snprintf(buffer + index, MAX_LEN - index, "%s,", files_arr[i]);
            index += file_len;
        }
        else
        {
            i--;
        }
        if (!(index + file_len < MAX_LEN) || i == num_files)
        {
            ret_value = send(socket_id, buffer, MAX_LEN, 0);
            if (ret_value < 0)
            {
                perror("send file names failed");
                return 1;
            }
            index = 0;
        }
    }
    return 0;
}
