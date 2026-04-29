/*
** EPITECH PROJECT, 2026
** libmy.a
** File description:
** this file countains the my_putchar functions
*/

#include <unistd.h>

void my_putchar_error(char c)
{
    write(2, &c, 1);
}

void my_putchar(char c)
{
    write(1, &c, 1);
}
