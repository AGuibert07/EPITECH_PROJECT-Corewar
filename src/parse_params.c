/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** main file of the project
*/

#include <stdlib.h>
#include <string.h>
#include "mem.h"
#include "my.h"

static int get_next_int_arg(const int ac, const char **av)
{
    if (ac == 0)
        return -1;
    if (!my_str_isnbr(av[0]))
        return -1;
    return my_getnbr(av[0]);
}

static int get_champion_arg(champion_t *champion, const int ac,
    const char **av)
{
    int tmp = 0;

    if (ac <= 2)
        return EPITECH_FAILURE;
    if (my_strcmp(av[1], "-n") == 0) {
        tmp = get_next_int_arg(ac - 1, av + 1);
        if (tmp < 0)
            return EPITECH_FAILURE;
        champion->champion_id = tmp;
    }
    if (my_strcmp(av[1], "-n") == 0) {
        tmp = get_next_int_arg(ac - 1, av + 1);
        if (tmp < 0)
            return EPITECH_FAILURE;
        champion->load_address = ABS(tmp) % MEM_SIZE;
    } else {
        print_error(av[0], ": Invalid option.\n");
        return EPITECH_FAILURE;
    }
    return EPITECH_SUCCESS;
}

static int parse_champion(const int ac, const char **av, champion_t *champion,
    size_t *pos)
{
    size_t i = 0;

    if (ac <= 0)
        return EPITECH_FAILURE;
    while (av[i][0] == '-') {
        if (get_champion_arg(champion, ac - i, av + i) != EPITECH_SUCCESS)
            return EPITECH_FAILURE;
        i += 2;
        *pos += 2;
    }
    if (ac - i <= 0) {
        my_putstr_error("corewar: Missing parameter 'prog name'.\n");
        return EPITECH_FAILURE;
    }
    champion->filename = (char *)(av[i]);
    *pos += 1;
    return EPITECH_SUCCESS;
}

static champion_t *get_champions(size_t i, const size_t ac, const char **av,
    size_t *ch_nbr)
{
    champion_t *champions = malloc(sizeof(champion_t));

    if (!champions)
        return NULL;
    *champions = null_champion;
    while (i < ac) {
        champions = realloc(champions, sizeof(champion_t) * (*ch_nbr + 2));
        if (!champions)
            return NULL;
        champions[*ch_nbr + 1] = null_champion;
        champions[*ch_nbr].alive = true;
        if (parse_champion(ac - i, &(av[i]), &(champions[*ch_nbr]), &i) !=
            EPITECH_SUCCESS) {
            free(champions);
            return NULL;
        }
        *ch_nbr += 1;
    }
    return champions;
}

static champion_t *check_champions_nbr(champion_t *champions, size_t ch_nbr)
{
    if (champions == NULL)
        return NULL;
    if (ch_nbr < MIN_CHAMPIONS_NBR) {
        my_putstr_error("corewar: Too few champions.\n");
        free(champions);
        return NULL;
    }
    if (ch_nbr > MAX_CHAMPIONS_NBR) {
        my_putstr_error("corewar: Too many champions.\n");
        free(champions);
        return NULL;
    }
    set_champions_id(champions, ch_nbr);
    set_champions_load_address(champions, ch_nbr);
    return champions;
}

champion_t *parse_arguments(const int ac, const char **av, size_t *ch_nbr,
    long *dump_value)
{
    champion_t *champions = NULL;
    size_t i = 1;

    *dump_value = -1;
    if (strcmp(av[1], "-dump") == 0) {
        i += 1;
        if (!my_str_isnbr(av[i])) {
            my_putstr_error(av[i]);
            my_putstr_error(": Invalid nbr_cycle value.\n");
            return NULL;
        }
        *dump_value = my_getnbr(av[i]);
        i += 1;
    }
    champions = get_champions(i, ac, av, ch_nbr);
    return check_champions_nbr(champions, *ch_nbr);
}
