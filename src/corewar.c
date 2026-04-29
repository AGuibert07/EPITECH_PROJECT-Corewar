/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains the corewar functions
*/

#include <stdbool.h>
#include "stream.h"
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

static void get_args_types(byte_t *virtual_memory, exec_stream_t *stream,
    args_type_t types[4])
{
    if (stream->instruction.coding_byte) {
        for (size_t i = 0; i < stream->instruction.nbr_args; ++i)
            types[i] = ((virtual_memory[stream->pos + stream->curent_byte] >>
                (MAX_ARGS_NUMBER - 1 - i) * 2) % MAX_ARGS_NUMBER) |
                (stream->instruction.type[i] & T_INDEX);
        stream->curent_byte += 1;
    } else
        for (size_t i = 0; i < stream->instruction.nbr_args; ++i)
            types[i] = stream->instruction.type[i];
}

static int get_argument(byte_t *virtual_memory, exec_stream_t *stream,
    args_type_t type)
{
    int arg = 0;

    for (size_t i = 0; i < stream->instruction.nbr_args; ++i) {
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

int execute_instruction(byte_t *virtual_memory, exec_stream_t *stream)
{
    args_type_t types[MAX_ARGS_NUMBER] = {0};
    int args[MAX_ARGS_NUMBER] = {0};

    get_args_types(virtual_memory, stream, types);
    for (size_t i = 0; i < stream->instruction.nbr_args; ++i)
        args[i] = get_argument(virtual_memory, stream, types[i]);
    return stream->instruction.op_function(virtual_memory, args,
        (void *)(stream));
}

int execute_tick(byte_t *virtual_memory, exec_stream_t *streams)
{
    for (size_t i = 0; streams[i].pos >= 0; ++i) {
        if (streams[i].inst_time <= 0) {
            streams[i].instruction =
                get_op_by_code(virtual_memory[streams[i].pos % MEM_SIZE]);
            streams[i].curent_byte = 1;
            streams[i].inst_time = streams[i].instruction.nbr_cycles - 1;
            streams[i].pos += ((streams[i].inst_time < 0) ? (1) : (0));
        } else if (streams[i].inst_time > 1)
            streams[i].inst_time -= 1;
        if (streams[i].inst_time == 1)
            execute_instruction(virtual_memory, &(streams[i]));
    }
}

int corewar(int champions_nbr, const char **filenames)
{
    byte_t *virtual_memory = NULL;
    exec_stream_t *streams = NULL;
    int registers[REG_NUMBER] = {0};
    bool loop = true;

    if (init_memory(champions_nbr, filenames, &virtual_memory, &streams) !=
        EPITECH_SUCCESS)
        return EPITECH_FAILURE;
    while (loop) {
        execute_tick(virtual_memory, streams);
    }
}
