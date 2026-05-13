/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains all functions to run an instruction
*/

#include <stdbool.h>
#include "mem.h"
#include "op.h"
#include "asm.h"
#include "my.h"

static void get_args_types(byte_t *virtual_memory, prog_stream_t *stream,
    args_type_t types[MAX_ARGS_NUMBER])
{
    byte_t cb = 0;

    if (stream->op.coding_byte) {
        cb = read_byte(virtual_memory, stream->pos + stream->curent_byte);
        stream->curent_byte += 1;
        for (int i = 0; i < stream->op.nbr_args; ++i)
            types[i] = ((cb >> (MAX_ARGS_NUMBER - 1 - i) * 2) % MAX_ARGS_NUMBER)
                | (stream->op.type[i] & T_INDEX);
    } else
        for (int i = 0; i < stream->op.nbr_args; ++i)
            types[i] = stream->op.type[i];
}

static int get_argument(byte_t *virtual_memory, prog_stream_t *stream,
    args_type_t type)
{
    int arg = 0;

    for (int i = 0; i < stream->op.nbr_args; ++i) {
        if (IS_REG(type)) {
            arg = read_byte(virtual_memory, stream->pos + stream->curent_byte);
            stream->curent_byte += T_REG;
            return arg;
        }
        if (IS_INDIR(type) || IS_INDEX(type)) {
            arg = read_byte(virtual_memory, stream->pos + stream->curent_byte);
            stream->curent_byte += T_IND;
            return arg;
        }
        if (IS_REG(type)) {
            arg = read_byte(virtual_memory, stream->pos + stream->curent_byte);
            stream->curent_byte += T_DIR;
            return arg;
        }
    }
    return 0;
}

int execute_instruction(byte_t *virtual_memory, size_t stream_index,
    global_data_t *global_data)
{
    prog_stream_t *stream = &(global_data->streams[stream_index]);

    get_args_types(virtual_memory, stream, stream->types);
    for (int i = 0; i < stream->op.nbr_args; ++i)
        stream->args[i] = get_argument(virtual_memory, stream,
            stream->types[i]);
    return stream->op.op_function(virtual_memory, stream, global_data);
}
