/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains the corewar functions
*/

#include <stdbool.h>
#include "mem.h"
#include "op.h"
#include "asm.h"
#include "my.h"

static op_t get_op_by_code(char code)
{
    size_t i = 0;

    for (; op_tab[i].mnemonique != NULL; ++i)
        if (op_tab[i].code == code)
            return op_tab[i];
    return op_tab[i];
}

static bool is_dead_and_clear(global_data_t *global_data, champion_t *champion)
{
    size_t n = 0;

    if (!champion->alive)
        return true;
    for (size_t i = 0; global_data->streams[i].champion_data; ++i)
        if (global_data->streams[i].champion_data->champion_id ==
            champion->champion_id)
            n += 1;
    return (n == 0);
}

void remove_stream(prog_stream_t *stream)
{
    if (stream[0].pos >= 0)
        for (size_t i = 0; stream[i].champion_data; ++i)
            stream[i] = stream[i + 1];
}

static void kill_champion(global_data_t *global_data, champion_t *champion)
{
    my_putstr(champion->prog_name);
    my_putstr(" is dead\n");
    for (int i = 0; global_data->streams[i].champion_data; ++i)
        if (global_data->streams[i].champion_data->champion_id ==
            champion->champion_id)
            remove_stream(&(global_data->streams[i]));
    champion->alive = false;
}

static void check_live(global_data_t *global_data)
{
    for (size_t i = 0; global_data->champions[i].filename; ++i) {
        if (!is_dead_and_clear(global_data, &(global_data->champions[i])) &&
            global_data->champions[i].live > global_data->nbr_lives) {
            kill_champion(global_data, &(global_data->champions[i]));
            global_data->alive_champions_nbr -= 1;
        }
    }
}

static bool get_next_instruction(byte_t *virtual_memory, prog_stream_t *stream)
{
    stream->op = get_op_by_code(
        read_byte(virtual_memory, stream->pos));
    if (stream->op.code == null_op.code)
        return false;
    stream->curent_byte = 1;
    stream->nbr_cycles = stream->op.nbr_cycles - 1;
    return true;
}

static void run_instruction(byte_t *virtual_memory, size_t stream_index,
    global_data_t *global_data, prog_stream_t *stream)
{
    execute_instruction(virtual_memory, stream_index, global_data);
    stream->pos += stream->curent_byte;
    stream->curent_byte = 0;
}

static int apply_tick_on_stream(byte_t *virtual_memory,
    global_data_t *global_data, prog_stream_t *stream, size_t stream_index)
{
    if (stream->nbr_cycles <= 0) {
        if (get_next_instruction(virtual_memory, stream))
            return 0;
        else {
            remove_stream(stream);
            return 1;
        }
    }
    if (stream->nbr_cycles > 1)
        stream->nbr_cycles -= 1;
    if (stream->op.code == null_op.code) {
        remove_stream(stream);
        return 1;
    }
    if (stream->nbr_cycles == 1)
        run_instruction(virtual_memory, stream_index, global_data, stream);
    return 0;
}

void execute_tick(byte_t *virtual_memory, global_data_t *global_data)
{
    for (size_t i = 0; global_data->champions[i].filename; ++i)
        global_data->champions[i].live += 1;
    for (int i = 0; global_data->streams[i].champion_data; ++i)
        i -= apply_tick_on_stream(virtual_memory, global_data,
            &(global_data->streams[i]), i);
    check_live(global_data);
    if (global_data->cycles > 1 &&
        global_data->cycles % global_data->nbr_lives == 0 &&
        global_data->nbr_lives > CYCLE_DELTA)
        global_data->nbr_lives -= CYCLE_DELTA;
}
