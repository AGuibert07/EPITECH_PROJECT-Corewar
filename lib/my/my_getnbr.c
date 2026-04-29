/*
** EPITECH PROJECT, 2026
** libmy.a
** File description:
** this file countains the my_getnbr function
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"

static bool is_int_over(char const *str, int length)
{
    char *max_int = "32767";
    int max_int_nb_digits = 5;

    if (length > max_int_nb_digits)
        return true;
    for (int i = 0; i < length; ++i) {
        if (length == max_int_nb_digits && str[i] > max_int[i])
            return true;
    }
    return false;
}

static int get_nbr_abs_val(char *str, int length)
{
    int nbr = 0;
    int index = 0;

    for (int i = (length - 1); i >= 0; i--) {
        nbr += (my_compute_power_rec(10, i) * (str[index] - 48));
        index += 1;
    }
    free(str);
    return nbr;
}

static char *get_nbr_part(char *str, int start_pos, int *length)
{
    int size = 0;

    for (int i = 0; (i < *length && my_is_in_str(str[i], "0123456789")); ++i) {
        size += 1;
    }
    *length = size;
    if (start_pos >= my_strlen(str))
        return my_substring(str, 0, 0);
    return my_substring(str, start_pos, size);
}

int my_getnbr(char const *str)
{
    int length = my_strlen(str);
    int sign = 1;
    int i = 0;
    char *nbr_part = NULL;

    while (my_is_in_str(str[i], DIGITS) != 1) {
        i += 1;
    }
    if (i > 0 && str[i - 1] == '-')
        sign = -1;
    length = length - i;
    nbr_part = get_nbr_part((char *)(str), i, &length);
    if (length >= 5) {
        if (is_int_over(nbr_part, length)) {
            free(nbr_part);
            return 0;
        }
    }
    return (get_nbr_abs_val(nbr_part, length) * sign);
}
