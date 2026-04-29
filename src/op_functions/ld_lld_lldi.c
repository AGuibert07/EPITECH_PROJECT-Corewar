/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains ld, lld, ldi and lldi instruction functions
*/

#include "mem.h"
#include "my.h"

int ld_instruction(byte_t *virtual_memory, exec_stream_t *stream,
    global_data_t *global_data)
{
    if (!IS_A_REG_ID(stream->args[1]))
        return EPITECH_FAILURE;
    if (IS_INDIR(stream->types[0]))
        global_data->registers[stream->args[1] - 1] =
            read_direct(virtual_memory, stream->pos + stream->args[0] %
                IDX_MOD);
    else
        global_data->registers[stream->args[1] - 1] = stream->args[0];
    return EPITECH_SUCCESS;
}

int lld_instruction(byte_t *virtual_memory, exec_stream_t *stream,
    global_data_t *global_data)
{
    if (!IS_A_REG_ID(stream->args[1]))
        return EPITECH_FAILURE;
    if (IS_INDIR(stream->types[0]))
        global_data->registers[stream->args[1] - 1] =
            read_direct(virtual_memory, stream->pos + stream->args[0]);
    else
        global_data->registers[stream->args[1] - 1] = stream->args[0];
    return EPITECH_SUCCESS;
}

int ldi_instruction(byte_t *virtual_memory, exec_stream_t *stream,
    global_data_t *global_data)
{
    int val1 = stream->args[0];
    int val2 = stream->args[1];

    if (!IS_A_REG_ID(stream->args[2]))
        return EPITECH_FAILURE;
    if (IS_REG(stream->types[0])) {
        if (!IS_A_REG_ID(val1))
            return EPITECH_FAILURE;
        val1 = global_data->registers[val1 - 1];
    }
    if (IS_REG(stream->types[1])) {
        if (!IS_A_REG_ID(val2))
            return EPITECH_FAILURE;
        val2 = global_data->registers[val2 - 1];
    }
    global_data->registers[stream->args[2] - 1] =
        read_direct(virtual_memory, stream->pos + (val1 + val2) % IDX_MOD);
    return EPITECH_SUCCESS;
}

int lldi_instruction(byte_t *virtual_memory, exec_stream_t *stream,
    global_data_t *global_data)
{
    int val1 = stream->args[0];
    int val2 = stream->args[1];

    if (!IS_A_REG_ID(stream->args[2]))
        return EPITECH_FAILURE;
    if (IS_REG(stream->types[0])) {
        if (!IS_A_REG_ID(val1))
            return EPITECH_FAILURE;
        val1 = global_data->registers[val1 - 1];
    }
    if (IS_REG(stream->types[1])) {
        if (!IS_A_REG_ID(val2))
            return EPITECH_FAILURE;
        val2 = global_data->registers[val2 - 1];
    }
    global_data->registers[stream->args[2] - 1] =
        read_direct(virtual_memory, stream->pos + val1 + val2);
    return EPITECH_SUCCESS;
}
