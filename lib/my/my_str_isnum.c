/*
** EPITECH PROJECT, 2026
** libmy.a
** File description:
** this file countains the my_str_isnum and the my_str_isnbr functions
*/

#include <stdbool.h>
#include "my.h"

bool my_str_isnum(char const *str)
{
    int size = my_strlen(str);

    if (size == 0)
        return false;
    for (int i = 0; i < size; ++i) {
        if (!my_is_in_str(str[i], DIGITS))
            return false;
    }
    return true;
}

bool my_str_isnbr(char const *str)
{
    int size = my_strlen(str);
    int start_pos = 0;

    if (size == 0)
        return false;
    if (str[0] == '-') {
        start_pos = 1;
        if (size == 1)
            return false;
    }
    for (int i = start_pos; i < size; ++i) {
        if (!my_is_in_str(str[i], DIGITS))
            return false;
    }
    return true;
}
