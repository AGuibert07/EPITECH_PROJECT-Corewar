/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains the corewar functions
*/

#include <stdbool.h>
#include <stdio.h>
#include <ncurses.h>
#include "mem.h"
#include "op.h"
#include "asm.h"
#include "my.h"

static int print_winner(champion_t *champions, size_t cycles)
{
    size_t n = 0;

    printf("Cycle : %i\n", cycles);
    for (size_t i = 0; champions[i].filename != NULL; ++i)
        if (champions[i].alive) {
            printf("%s is winner.\n", champions[i].prog_name);
            n += 1;
        }
    if (n == 0)
        printf("Everybody is dead.\n");
    if (n > 1)
        return EPITECH_FAILURE;
    return EPITECH_SUCCESS;
}

static void init_ncurses(void)
{
    initscr();
    keypad(stdscr, FALSE);
}

static void update_display(byte_t *virtual_memory, global_data_t *global_data)
{
    global_data->cycles += 1;
    execute_tick(virtual_memory, global_data);
    clear();
    dump_vm(virtual_memory, global_data);
    refresh();
}

int corewar(const int ac, const char **av)
{
    global_data_t global_data = {0, 0, {0}, NULL, NULL, 0, -1, 0};
    byte_t *virtual_memory = init_memory(ac, av, &global_data);
    int r_val = 0;

    if (virtual_memory == NULL) {
        print_error("corewar", "Can't initialize the virtual memory.");
        return EPITECH_FAILURE;
    }
    if (global_data.dump_val == 0)
        dump_vm(virtual_memory, &global_data);
    init_ncurses();
    while (global_data.alive_champions_nbr > 1)
        update_display(virtual_memory, &global_data);
    endwin();
    r_val = print_winner(global_data.champions, global_data.cycles);
    nfree(3, virtual_memory, global_data.champions, global_data.streams);
    return r_val;
}
