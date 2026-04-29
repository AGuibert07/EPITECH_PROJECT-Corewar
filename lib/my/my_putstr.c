/*
** EPITECH PROJECT, 2026
** libmy.a
** File description:
** this file countains the my_putstr functions
*/

#include <unistd.h>
#include "my.h"

void my_putstr(char const *str)
{
    write(1, str, my_strlen(str));
}

void my_putstr_error(char const *str)
{
    write(2, str, my_strlen(str));
}
