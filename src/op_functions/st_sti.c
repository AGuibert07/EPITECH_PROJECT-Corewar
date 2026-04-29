/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains st and sti instruction functions
*/

#include "mem.h"
#include "my.h"

int st_instruction(byte_t *virtual_memory, exec_stream_t *stream,
    global_data_t *global_data)
{
    if (!IS_A_REG_ID(stream->args[0]))
        return EPITECH_FAILURE;
    if (IS_REG(stream->types[1])) {
        if (!IS_A_REG_ID(stream->args[1]))
            return EPITECH_FAILURE;
        global_data->registers[stream->args[1] - 1] =
            global_data->registers[stream->args[0] - 1];
    } else
        write_direct(virtual_memory, stream->pos + stream->args[1],
            global_data->registers[stream->args[0] - 1]);
    return EPITECH_SUCCESS;
}

int sti_instruction(byte_t *virtual_memory, exec_stream_t *stream,
    global_data_t *global_data)
{
    int val1 = stream->args[1];
    int val2 = stream->args[2];

    if (!IS_A_REG_ID(stream->args[0]))
        return EPITECH_FAILURE;
    if (IS_REG(stream->types[1])) {
        if (!IS_A_REG_ID(val1))
            return EPITECH_FAILURE;
        val1 = global_data->registers[val1 - 1];
    }
    if (IS_REG(stream->types[2])) {
        if (!IS_A_REG_ID(val2))
            return EPITECH_FAILURE;
        val2 = global_data->registers[val2 - 1];
    }
    write_direct(virtual_memory, stream->pos + (val1 + val2) % IDX_MOD,
        global_data->registers[stream->args[0] - 1]);
    return EPITECH_SUCCESS;
}
