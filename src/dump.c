/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains the corewar functions
*/

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include "mem.h"
#include "op.h"
#include "asm.h"
#include "my.h"

static void print_byte_as_hex(byte_t value)
{
    const size_t nbr_hex_char = __CHAR_BIT__ / 4;
    size_t shift = 0;

    for (size_t i = 0; i < nbr_hex_char; ++i) {
        shift = (nbr_hex_char - i - 1) * (__CHAR_BIT__ / nbr_hex_char);
        my_putchar(UP_HEXA_DIGITS[(value >> shift) % 16]);
    }
}

static void print_int_as_hex(int value)
{
    for (int i = (sizeof(int) - 1); i >= 0; --i)
        print_byte_as_hex((value >> (__CHAR_BIT__ * i)) % _2_POW_8);
}

static void dump_register(size_t id, int value)
{
    my_putchar('r');
    my_put_nbr(id);
    if (id < 10)
        my_putchar(' ');
    my_putstr(": ");
    print_int_as_hex(value);
    if (id < REG_NUMBER)
        my_putstr("    ");
}

static void dump_stream(prog_stream_t *stream)
{
    my_putstr(" \n");
    my_putstr(stream->champion_data->prog_name);
    my_putchar('(');
    my_put_nbr(stream->champion_data->champion_id);
    my_putstr("): ");
    if (stream->champion_data->alive)
        my_putstr("alive");
    else
        my_putstr("dead");
    my_putstr("\n    ");
    for (size_t i = 0; i < REG_NUMBER; ++i)
        dump_register(i + 1, stream->registers[i]);
    my_putstr("\n    PC : ");
    print_int_as_hex(stream->pos);
    my_putstr("    carry: ");
    my_put_nbr(stream->carry);
    my_putchar('\n');
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
    my_putstr("Memory:   ");
    for (byte_t i = 0; i < NBR_COLUMNS; ++i) {
        if (i > 0)
            my_putchar(' ');
        print_byte_as_hex(i);
    }
    my_putchar('\n');
    for (byte_t i = 0; i < (NBR_COLUMNS + 3); ++i)
        my_putstr(" --");
    my_putchar('\n');
    for (size_t l = 0; l < (MEM_SIZE / NBR_COLUMNS); ++l) {
        print_int_as_hex(l * 32);
        my_putchar(':');
        for (size_t r = 0; r < NBR_COLUMNS; ++r) {
            my_putchar(' ');
            print_byte_as_hex(read_byte(virtual_memory, (l * NBR_COLUMNS) + r));
        }
        my_putchar('\n');
    }
}

void dump_vm(byte_t *virtual_memory, global_data_t *global_data)
{
    my_putstr("Cycle: ");
    my_put_nbr(global_data->cycles);
    my_putstr("\nRegisters:\n");
    for (size_t i = 0; global_data->champions[i].filename != NULL; ++i)
        dump_champion(global_data, &(global_data->champions[i]));
    my_putchar('\n');
    dump_memory(virtual_memory);
}
