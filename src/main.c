/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** main file of the project
*/

#include "mem.h"
#include "my.h"

void print_help(void)
{
    my_putstr("USAGE\n./corewar [-dump nbr_cycle] ");
    my_putstr("[[-n prog_number] [-a load_address] prog_name] ...\n");
    my_putstr("DESCRIPTION\n-dump nbr_cycle dumps the state of the virtual ");
    my_putstr("machine after the nbr_cycle execution\n");
    my_putstr("-n prog_number sets the next program's number. By default, ");
    my_putstr("the first free number in the parameter order\n");
    my_putstr("-a load_address sets the next program's loading address. ");
    my_putstr("When no address is specified, optimize the addresses so that ");
    my_putstr("the processes are far away from each other as possible. ");
    my_putstr("The addresses are MEM_SIZE modulo.\n");
}

int main(int ac, const char **av)
{
    if (my_is_in_word_array("-h", av)) {
        print_help();
        return EPITECH_SUCCESS;
    }
    if ((ac - 1) < MIN_CHAMPIONS_NBR) {
        my_putstr_error("corewar: Too few champions : must load at least ");
        my_put_nbr_error(MIN_CHAMPIONS_NBR);
        my_putstr_error(" champions.\n");
    } else if ((ac - 1) > MAX_CHAMPIONS_NBR) {
        my_putstr_error("corewar: Too many champions : must load at most ");
        my_put_nbr_error(MAX_CHAMPIONS_NBR);
        my_putstr_error(" champions.\n");
    }
    return corewar(ac - 1, av);
}
