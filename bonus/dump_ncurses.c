/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains the corewar functions
*/

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <ncurses.h>
#include "mem.h"
#include "op.h"
#include "asm.h"
#include "my.h"

static void dump_register(size_t id, int value)
{
    printw("r%i", id);
    if (id < 10)
        printw(" ");
    printw(": %.8hX", value);
    if (id < REG_NUMBER)
        printw("%4s", "");
}

static void dump_stream(prog_stream_t *stream)
{
    printw(" \n%s(%i): ", stream->champion_data->prog_name,
        stream->champion_data->champion_id);
    if (stream->champion_data->alive)
        printw("alive");
    else
        printw("dead");
    printw("\n%4s", "");
    for (size_t i = 0; i < REG_NUMBER; ++i)
        dump_register(i + 1, stream->registers[i]);
    printw("\n    PC : %.8hX    carry: %i\n", stream->pos, stream->carry);
}

static void dump_champion(global_data_t *global_data,
    champion_t *champion)
{
    for (size_t i = 0; global_data->streams[i].champion_data != NULL; ++i)
        if (global_data->streams[i].champion_data->champion_id ==
            champion->champion_id)
            dump_stream(&(global_data->streams[i]));
}

static void dump_memory(byte_t *virtual_memory)
{
    printw("Memory:%3s", "");
    for (byte_t i = 0; i < NBR_COLUMNS; ++i) {
        if (i > 0)
            printw(" ");
        printw("%.2hX", i);
    }
    printw("\n");
    for (byte_t i = 0; i < (NBR_COLUMNS + 3); ++i)
        printw(" --");
    printw("\n");
    for (size_t l = 0; l < (MEM_SIZE / NBR_COLUMNS); ++l) {
        printw("%.8hX:", l * 32);
        for (size_t r = 0; r < NBR_COLUMNS; ++r)
            printw(" %.2hX", read_byte(virtual_memory, (l * NBR_COLUMNS) + r));
        printw("\n");
    }
}

void dump_vm(byte_t *virtual_memory, global_data_t *global_data)
{
    printw("Cycle: %i\nRegisters:\n", global_data->cycles);
    for (size_t i = 0; global_data->champions[i].filename != NULL; ++i)
        dump_champion(global_data, &(global_data->champions[i]));
    printw("\n");
    dump_memory(virtual_memory);
}
