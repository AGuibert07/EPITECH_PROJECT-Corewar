/*
** EPITECH PROJECT, 2026
** libmy.a
** File description:
** this file countains the my_strcmp function
*/

#include "my.h"

static int comparison(const char *s1, const char *s2, int *sizes, int i)
{
    int size1 = sizes[0];
    int size2 = sizes[1];
    char c1;
    char c2;

    if (i < size1)
        c1 = s1[i];
    else
        c1 = '\0';
    if (i < size2)
        c2 = s2[i];
    else
        c2 = '\0';
    return (c1 - c2);
}

int my_strcmp(char const *s1, char const *s2)
{
    int sizes[2] = {my_strlen(s1), my_strlen(s2)};
    int nb_it;

    if (s1 == s2)
        return 0;
    if (s1 == NULL)
        return *s2;
    if (s2 == NULL)
        return *s1;
    if (sizes[0] >= sizes[1])
        nb_it = sizes[0];
    else
        nb_it = sizes[1];
    for (int i = 0; i < nb_it; ++i) {
        if (comparison(s1, s2, sizes, i) != 0)
            return comparison(s1, s2, sizes, i);
    }
    return 0;
}
