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
    printw("r%zu", id);
    if (id < 10)
        printw(" ");
    printw(": %.8hX", value);
    if (id < REG_NUMBER)
        printw("%4s", "");
}

static void dump_stream(prog_stream_t *stream)
{
    printw(" \n%s(%zu): ", stream->champion_data->prog_name,
        stream->champion_data->champion_id);
    if (stream->champion_data->alive)
        printw("alive");
    else
        printw("dead");
    printw("\n%4s", "");
    for (size_t i = 0; i < REG_NUMBER; ++i)
        dump_register(i + 1, stream->registers[i]);
    printw("\n    PC : %.8zX    carry: %i\n", stream->pos, stream->carry);
}

static void dump_champion(global_data_t *global_data,
    champion_t *champion)
{
    for (size_t i = 0; global_data->streams[i].champion_data != NULL; ++i)
        if (global_data->streams[i].champion_data->champion_id ==
            champion->champion_id)
            dump_stream(&(global_data->streams[i]));
}

static ncolor_t get_byte_color(size_t byte_pos, prog_stream_t *streams)
{
    ncolor_t color = DEFAULT;
    size_t load_add = 0;
    size_t prog_size = 0;

    for (size_t i = 0; streams[i].champion_data; ++i) {
        load_add = streams[i].champion_data->load_address;
        prog_size = streams[i].champion_data->prog_size;
        if (streams[i].pos == byte_pos && color < STREAM)
            color = STREAM;
        if (streams[i].pos < byte_pos &&
            (streams[i].pos + streams[i].curent_byte) % MEM_SIZE > byte_pos
            && color < READ)
            color = READ;
        if (load_add == byte_pos && color < START)
            color = START;
        if (load_add < byte_pos && (load_add + prog_size) % MEM_SIZE > byte_pos
            && color < PROG)
            color = PROG;
    }
    return color;
}

static void dump_memory(byte_t *virtual_memory, prog_stream_t *streams)
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
        attron(COLOR_PAIR(DEFAULT));
        printw("%.8zX:", l * 32);
        for (size_t r = 0; r < NBR_COLUMNS; ++r) {
            attron(COLOR_PAIR(get_byte_color((l * NBR_COLUMNS) + r, streams)));
            printw(" %.2hX", read_byte(virtual_memory, (l * NBR_COLUMNS) + r));
        }
        printw("\n");
    }
    attron(COLOR_PAIR(DEFAULT));
}

void dump_vm(byte_t *virtual_memory, global_data_t *global_data)
{
    attron(COLOR_PAIR(DEFAULT));
    printw("Cycle: %zu\nRegisters:\n", global_data->cycles);
    for (size_t i = 0; global_data->champions[i].filename != NULL; ++i)
        dump_champion(global_data, &(global_data->champions[i]));
    printw("\n");
    dump_memory(virtual_memory, global_data->streams);
}
