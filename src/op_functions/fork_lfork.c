/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains fork and lfork instruction functions
*/

#include <stdlib.h>
#include "mem.h"
#include "my.h"

static void set_new_stream(exec_stream_t *new_stream, int pos)
{
    new_stream->pos = pos;
    new_stream->curent_byte = 0;
    new_stream->inst_time = -1;
    for (size_t i = 0; i < MAX_ARGS_NUMBER; ++i) {
        new_stream->types[i] = 0;
        new_stream->args[i] = 0;
    }
    new_stream->instruction = null_op;
    new_stream->running = true;
}

int fork_instruction(byte_t *virtual_memory, exec_stream_t *stream,
    global_data_t *global_data)
{
    global_data->streams = realloc(global_data->streams,
        sizeof(exec_stream_t) * (global_data->progs_nbr + 2));
    if (global_data->streams == NULL)
        return EPITECH_FAILURE;
    global_data->progs_nbr += 1;
    global_data->streams[global_data->progs_nbr] = null_stream;
    set_new_stream(&(global_data->streams[global_data->progs_nbr - 1]),
        stream->pos + stream->args[0] % IDX_MOD);
    return EPITECH_SUCCESS;
}

int lfork_instruction(byte_t *virtual_memory, exec_stream_t *stream,
    global_data_t *global_data)
{
    global_data->streams = realloc(global_data->streams,
        sizeof(exec_stream_t) * (global_data->progs_nbr + 2));
    if (global_data->streams == NULL)
        return EPITECH_FAILURE;
    global_data->progs_nbr += 1;
    global_data->streams[global_data->progs_nbr] = null_stream;
    set_new_stream(&(global_data->streams[global_data->progs_nbr - 1]),
        stream->pos + stream->args[0]);
    return EPITECH_SUCCESS;
}
