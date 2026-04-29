/*
** EPITECH PROJECT, 2026
** libmy.a
** File description:
** this file countains the my_strlen function
*/

#include <stdio.h>

int my_strlen(char const *str)
{
    int length = 0;

    if (str == NULL)
        return -1;
    while (str[length] != '\0')
        length += 1;
    return length;
}
