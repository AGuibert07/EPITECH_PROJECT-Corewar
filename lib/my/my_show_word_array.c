/*
** EPITECH PROJECT, 2026
** libmy.a
** File description:
** this file countains the my_show_word_array function
*/

#include <stdio.h>
#include "my.h"

void my_show_word_array(char const **tab)
{
    for (int i = 0; tab[i] != 0; ++i) {
        my_putstr(tab[i]);
        my_putchar('\n');
    }
}
