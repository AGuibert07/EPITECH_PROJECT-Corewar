/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains add, sub, and, or and xor instruction functions
*/

#include "mem.h"
#include "my.h"

int add_instruction(byte_t *virtual_memory, exec_stream_t *stream,
    global_data_t *global_data)
{
    if (!(IS_A_REG_ID(stream->args[0]) && IS_A_REG_ID(stream->args[1]) &&
        IS_A_REG_ID(stream->args[2])))
        return EPITECH_FAILURE;
    global_data->registers[stream->args[2] - 1] =
        global_data->registers[stream->args[0] - 1] +
        global_data->registers[stream->args[1] - 1];
    return EPITECH_SUCCESS;
}

int sub_instruction(byte_t *virtual_memory, exec_stream_t *stream,
    global_data_t *global_data)
{
    if (!(IS_A_REG_ID(stream->args[0]) && IS_A_REG_ID(stream->args[1]) &&
        IS_A_REG_ID(stream->args[2])))
        return EPITECH_FAILURE;
    global_data->registers[stream->args[2] - 1] =
        global_data->registers[stream->args[0] - 1] -
        global_data->registers[stream->args[1] - 1];
    return EPITECH_SUCCESS;
}

int and_instruction(byte_t *virtual_memory, exec_stream_t *stream,
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
    } else if (IS_INDIR(stream->types[0]))
        val1 += stream->pos;
    if (IS_REG(stream->types[1])) {
        if (!IS_A_REG_ID(val2))
            return EPITECH_FAILURE;
        val2 = global_data->registers[val2 - 1];
    } else if (IS_INDIR(stream->types[1]))
        val2 += stream->pos;
    global_data->registers[stream->args[2] - 1] = val1 & val2;
    return EPITECH_SUCCESS;
}

int or_instruction(byte_t *virtual_memory, exec_stream_t *stream,
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
    } else if (IS_INDIR(stream->types[0]))
        val1 += stream->pos;
    if (IS_REG(stream->types[1])) {
        if (!IS_A_REG_ID(val2))
            return EPITECH_FAILURE;
        val2 = global_data->registers[val2 - 1];
    } else if (IS_INDIR(stream->types[1]))
        val2 += stream->pos;
    global_data->registers[stream->args[2] - 1] = val1 | val2;
    return EPITECH_SUCCESS;
}

int xor_instruction(byte_t *virtual_memory, exec_stream_t *stream,
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
    } else if (IS_INDIR(stream->types[0]))
        val1 += stream->pos;
    if (IS_REG(stream->types[1])) {
        if (!IS_A_REG_ID(val2))
            return EPITECH_FAILURE;
        val2 = global_data->registers[val2 - 1];
    } else if (IS_INDIR(stream->types[1]))
        val2 += stream->pos;
    global_data->registers[stream->args[2] - 1] = val1 ^ val2;
    return EPITECH_SUCCESS;
}
