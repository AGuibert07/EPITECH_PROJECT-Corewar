/*
** EPITECH PROJECT, 2026
** libmy.a
** File description:
** this file countains string tools functions
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include "my.h"

bool str_start_with(const char *str, const char *pattern)
{
    int l_pattern = my_strlen(pattern);

    if (my_strlen(str) < l_pattern)
        return false;
    for (int i = 0; i < l_pattern; ++i)
        if (str[i] != pattern[i])
            return false;
    return true;
}

int my_nbr_occ_str(const char *str, const char *pattern)
{
    int count = 0;
    int l_str = my_strlen(str);
    int l_pattern = my_strlen(pattern);

    if (str == NULL || pattern == NULL)
        return -1;
    for (int i = 0; i <= (l_str - l_pattern); ++i) {
        if (str_start_with(&(str[i]), pattern))
            count += 1;
    }
    return count;
}

static int get_index_next_occ(const char *str, const char *pattern)
{
    int l_str = my_strlen(str);
    int l_pattern = my_strlen(pattern);

    for (int i = 0; i <= (l_str - l_pattern); ++i)
        if (str_start_with(&(str[i]), pattern))
            return i;
    return -1;
}

char **my_split_str2(char *str, const char *sep)
{
    const int nbr_occ = my_nbr_occ_str(str, sep);
    char **arr = NULL;
    int i_next = 0;

    if (str == NULL || sep == NULL)
        return NULL;
    arr = malloc(sizeof(char *) * (nbr_occ + 1));
    for (int i = 0; i <= nbr_occ; ++i)
        arr[i] = NULL;
    for (int i = 0; i < (nbr_occ - 1); ++i) {
        i_next = get_index_next_occ(str, sep);
        arr[i] = my_substring(str, 0, i_next);
        str = &(str[i_next + my_strlen(sep)]);
    }
    arr[nbr_occ - 1] = my_strdup((const char *)(str));
    if (my_word_array_len(arr) != nbr_occ) {
        sfree_array(arr, nbr_occ);
        return NULL;
    }
    return arr;
}
