/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains the corewar functions
*/

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include "mem.h"
#include "op.h"
#include "asm.h"
#include "my.h"

static int print_winner(champion_t *champions, size_t cycles)
{
    size_t n = 0;

    printf("Cycle : %zu\n", cycles);
    for (size_t i = 0; champions[i].filename != NULL; ++i)
        if (champions[i].alive) {
            printf("The player %zu(%s)has won.", champions[i].champion_id,
                champions[i].prog_name);
            n += 1;
        }
    if (n == 0)
        printf("No player has won.\n");
    if (n > 1)
        return EPITECH_FAILURE;
    return EPITECH_SUCCESS;
}

static void init_ncurses(void)
{
    initscr();
    start_color();
    init_pair(DEFAULT, COLOR_WHITE, COLOR_BLACK);
    init_pair(PROG, COLOR_BLUE, COLOR_BLACK);
    init_pair(READ, COLOR_YELLOW, COLOR_BLACK);
    init_pair(START, COLOR_GREEN, COLOR_BLACK);
    init_pair(STREAM, COLOR_RED, COLOR_BLACK);
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

static int end_game(global_data_t *global_data, byte_t *virtual_memory)
{
    int r_val = print_winner(global_data->champions, global_data->cycles - 1);

    endwin();
    nfree(3, virtual_memory, global_data->champions, global_data->streams);
    return r_val;
}

int corewar(const int ac, const char **av)
{
    global_data_t global_data = {0, 0, {0}, NULL, NULL, 0, -1, 0, CYCLE_TO_DIE};
    byte_t *virtual_memory = init_memory(ac, av, &global_data);
    size_t tdump = ((global_data.dump_val >= 0) ? (global_data.dump_val) : (0));

    if (virtual_memory == NULL)
        return EPITECH_FAILURE;
    dump_vm(virtual_memory, &global_data);
    init_ncurses();
    while (global_data.alive_champions_nbr > 1 || (global_data.cycles <= tdump
            && tdump >= 0)) {
        sleep(DELAY);
        update_display(virtual_memory, &global_data);
    }
    return end_game(&global_data, virtual_memory);
}
