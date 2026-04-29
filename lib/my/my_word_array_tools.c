/*
** EPITECH PROJECT, 2026
** libmy.a
** File description:
** this file countains word array tool functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "my.h"

int my_index_of_word_array(char *str, char **arr)
{
    if (str == NULL || arr == NULL)
        return -1;
    for (int i = 0; arr[i] != 0; ++i)
        if (my_strcmp(str, arr[i]) == 0)
            return i;
    return -1;
}

char **my_word_array_concat(char **arr1, char **arr2)
{
    int size1 = 0;
    int size2 = 0;
    char **arr;
    int index = 0;

    if (arr1 == NULL || arr2 == NULL)
        return NULL;
    size1 = my_word_array_len((const char **)(arr1));
    size2 = my_word_array_len((const char **)(arr2));
    arr = malloc(sizeof(char *) * (size1 + size2 + 1));
    for (int i = 0; i < size1; ++i) {
        arr[index] = my_strdup(arr1[i]);
        index += 1;
    }
    for (int i = 0; i < size2; ++i) {
        arr[index] = my_strdup(arr2[i]);
        index += 1;
    }
    arr[index] = 0;
    return arr;
}

bool my_is_in_word_array(char *str, char **arr)
{
    for (int i = 0; i < my_word_array_len((const char **)(arr)); ++i) {
        if (my_strcmp(str, arr[i]) == 0)
            return true;
    }
    return false;
}

char **my_string_arr_dup(char **arr)
{
    int size = my_word_array_len((const char **)(arr));
    char **arr_new = malloc(sizeof(char *) * (size + 1));

    if (arr_new == NULL)
        return NULL;
    for (int i = 0; i < size; ++i) {
        arr_new[i] = my_strdup(arr[i]);
        if (arr_new[i] == NULL) {
            free(arr_new);
            return NULL;
        }
    }
    arr_new[size] = 0;
    return arr_new;
}
