/*
** EPITECH PROJECT, 2026
** libmy.a
** File description:
** this file countains the my_strdup and my_calloc functions
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

void *my_calloc(size_t size)
{
    char *arr = malloc(size);

    if (arr == NULL)
        return NULL;
    for (size_t i = 0; i < size; ++i)
        arr[i] = 0;
    return arr;
}

char *my_strdup(char const *str)
{
    int size = 0;
    char *new_str = NULL;

    if (str == NULL)
        return NULL;
    size = my_strlen(str);
    new_str = malloc(sizeof(char) * (size + 1));
    if (new_str == NULL)
        return NULL;
    for (int i = 0; i < size; ++i)
        new_str[i] = str[i];
    new_str[size] = '\0';
    return new_str;
}
