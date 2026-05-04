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

static void get_args_types(byte_t *virtual_memory, exec_stream_t *stream,
    args_type_t types[4])
{
    if (stream->instruction.coding_byte) {
        for (int i = 0; i < stream->instruction.nbr_args; ++i)
            types[i] = ((virtual_memory[stream->pos + stream->curent_byte] >>
                    (MAX_ARGS_NUMBER - 1 - i) * 2) % MAX_ARGS_NUMBER) |
                (stream->instruction.type[i] & T_INDEX);
        stream->curent_byte += 1;
    } else
        for (int i = 0; i < stream->instruction.nbr_args; ++i)
            types[i] = stream->instruction.type[i];
}

static int get_argument(byte_t *virtual_memory, exec_stream_t *stream,
    args_type_t type)
{
    int arg = 0;

    for (int i = 0; i < stream->instruction.nbr_args; ++i) {
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
    exec_stream_t *stream = &(global_data->streams[stream_index]);

    get_args_types(virtual_memory, stream, stream->types);
    for (int i = 0; i < stream->instruction.nbr_args; ++i)
        stream->args[i] = get_argument(virtual_memory, stream,
            stream->types[i]);
    return stream->instruction.op_function(virtual_memory, stream, global_data);
}

void execute_tick(byte_t *virtual_memory, global_data_t *global_data)
{
    for (size_t i = 0; i < global_data->alive_champions_nbr; ++i)
        global_data->lives[i] += 1;
    for (size_t i = 0; global_data->streams[i].pos >= 0; ++i) {
        if (global_data->streams[i].inst_time > 1)
            global_data->streams[i].inst_time -= 1;
        if (global_data->streams[i].inst_time <= 0) {
            global_data->streams[i].instruction = get_op_by_code(
                virtual_memory[global_data->streams[i].pos % MEM_SIZE]);
            global_data->streams[i].curent_byte = 1;
            global_data->streams[i].inst_time =
                global_data->streams[i].instruction.nbr_cycles - 1;
            global_data->streams[i].pos +=
                ((global_data->streams[i].inst_time < 0) ? (1) : (0));
        }
        if (global_data->streams[i].inst_time == 1) {
            execute_instruction(virtual_memory, i, global_data);
            global_data->streams[i].pos += global_data->streams[i].curent_byte;
            global_data->streams[i].curent_byte = 0;
        }
    }
}

int corewar(int champions_nbr, const char **filenames)
{
    byte_t *virtual_memory = NULL;
    bool loop = true;
    global_data_t global_data = {champions_nbr, {0}, NULL, 0};

    if (init_memory(champions_nbr, filenames, &virtual_memory,
            &(global_data.streams)) !=
        EPITECH_SUCCESS)
        return EPITECH_FAILURE;
    while (loop) {
        execute_tick(virtual_memory, &global_data);
    }
    return EPITECH_SUCCESS;
}
