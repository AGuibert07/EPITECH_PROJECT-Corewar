/*
** EPITECH PROJECT, 2026
** libmy.a
** File description:
** this file countains all functions to get the content of a file
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my.h"

static char **remove_blank_ending_lines(char **arr)
{
    int l = my_word_array_len((const char **)(arr));

    if (arr == NULL)
        return NULL;
    for (int i = (l - 1); i >= 0; --i) {
        if (my_strlen(arr[i]) == 0) {
            free(arr[i]);
            arr[i] = 0;
        } else
            i = -1;
    }
    return arr;
}

char **read_file(FILE *file, int buffer_size)
{
    size_t size = buffer_size;
    char *buffer = NULL;
    char **arr = NULL;

    if (buffer_size <= 0)
        return NULL;
    buffer = my_calloc(buffer_size + 1);
    if (buffer == NULL)
        return NULL;
    size = fread(buffer, sizeof(char), buffer_size, file);
    if (size < 0)
        return NULL;
    arr = my_split_str(buffer, "\n");
    if (arr == NULL)
        return NULL;
    free(buffer);
    return remove_blank_ending_lines(arr);
}

int get_file_size(char *filename)
{
    struct stat *sb = malloc(sizeof(struct stat));
    int file_size = 0;

    if (sb == NULL)
        return -1;
    file_size = stat(filename, sb);
    if (file_size < 0)
        return -1;
    file_size = (*sb).st_size;
    free(sb);
    return file_size;
}

char **get_file_content(char *filename)
{
    int file_size = get_file_size(filename);
    FILE *file = NULL;
    char **content = NULL;

    if (file_size <= 0)
        return NULL;
    file = fopen(filename, "r");
    if (file == NULL)
        return NULL;
    content = read_file(file, file_size);
    fclose(file);
    return content;
}
