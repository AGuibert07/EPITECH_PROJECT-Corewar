/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** main file of the project
*/

#include "stream.h"
#include "my.h"

int main(int ac, const char **av)
{
    if ((ac - 1) < MIN_CHAMPIONS_NBR) {
        my_putstr_error("corewar: Too few champions : must load at least ");
        my_put_nbr_error(MIN_CHAMPIONS_NBR);
        my_putstr_error(" champions.\n");
    } else if ((ac - 1) > MAX_CHAMPIONS_NBR) {
        my_putstr_error("corewar: Too many champions : must load at most ");
        my_put_nbr_error(MAX_CHAMPIONS_NBR);
        my_putstr_error(" champions.\n");
    }
}
