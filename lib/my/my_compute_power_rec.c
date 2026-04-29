/*
** EPITECH PROJECT, 2026
** libmy.a
** File description:
** this file countains the my_compute_power_rec function
*/

#include "my.h"

static int compute_power(int nb, int p)
{
    int r = 1;

    r = my_compute_power_rec(nb, p - 1);
    if (ABS(r) >= 2147483647 / ABS(nb)) {
        return (0);
    } else {
        return r * nb;
    }
}

int my_compute_power_rec(int nb, int p)
{
    if (p == 0) {
        return 1;
    } else if (p < 0 || nb == 0) {
        return 0;
    } else {
        return compute_power(nb, p);
    }
}
