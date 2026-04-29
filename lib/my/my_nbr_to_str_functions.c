/*
** EPITECH PROJECT, 2026
** libmy.a
** File description:
** this file countains the my_int_to_str_convertion function;
*/

#include <stdlib.h>
#include "my.h"

static char *convert_char_to_str(char c)
{
    char *str = malloc(sizeof(char) * 2);

    if (str == NULL)
        return NULL;
    str[0] = c;
    str[1] = '\0';
    return str;
}

static int get_nbr_digits(long long int nbr, int base)
{
    int nbr_digits = -1;

    if (nbr < 0)
        nbr = -nbr;
    while (my_compute_power_rec(base, nbr_digits + 1) <= nbr) {
        nbr_digits += 1;
    }
    return nbr_digits + 1;
}

static char *concat_nbr_digits(long long int nbr, const char *base,
    unsigned int nbr_digits)
{
    int power_val = 0;
    char *str_char = NULL;
    char *temp = NULL;
    char *str = NULL;

    if (nbr_digits == 0)
        return my_strdup("");
    power_val = my_compute_power_rec(my_strlen(base), nbr_digits - 1);
    str_char = convert_char_to_str(base[nbr / power_val]);
    temp = concat_nbr_digits(nbr % power_val, base, nbr_digits - 1);
    if (str_char == NULL || temp == NULL) {
        nfree(2, str_char, temp);
        return NULL;
    }
    str = my_str_concat(str_char, temp);
    nfree(2, temp, str_char);
    return str;
}

char *my_int_to_str_function(long long int nbr, const char *base)
{
    int nbr_digits = get_nbr_digits(nbr, my_strlen(base));
    int sign = 0;
    char *str = NULL;
    char *temp = NULL;

    if (nbr == 0)
        return convert_char_to_str(base[0]);
    sign = SIGN(nbr);
    nbr = ABS(nbr);
    if (nbr_digits <= 1)
        str = convert_char_to_str(base[nbr]);
    str = concat_nbr_digits(nbr, base, nbr_digits);
    if (str == NULL)
        return NULL;
    if (sign < 0) {
        temp = str;
        str = my_str_concat("-", temp);
        free(temp);
    }
    return str;
}
