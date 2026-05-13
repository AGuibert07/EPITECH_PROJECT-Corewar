/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains add, sub, and, or and xor instruction functions
*/

#include "mem.h"
#include "my.h"

int add_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data)
{
    HIDE_UNUSED_PTR(virtual_memory);
    HIDE_UNUSED_PTR(global_data);
    if (!(IS_A_REG_ID(stream->args[0]) && IS_A_REG_ID(stream->args[1]) &&
            IS_A_REG_ID(stream->args[2])))
        return EPITECH_FAILURE;
    stream->registers[stream->args[2] - 1] =
        stream->registers[stream->args[0] - 1] +
        stream->registers[stream->args[1] - 1];
    return EPITECH_SUCCESS;
}

int sub_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data)
{
    HIDE_UNUSED_PTR(virtual_memory);
    HIDE_UNUSED_PTR(global_data);
    if (!(IS_A_REG_ID(stream->args[0]) && IS_A_REG_ID(stream->args[1]) &&
            IS_A_REG_ID(stream->args[2])))
        return EPITECH_FAILURE;
    stream->registers[stream->args[2] - 1] =
        stream->registers[stream->args[0] - 1] -
        stream->registers[stream->args[1] - 1];
    return EPITECH_SUCCESS;
}

int and_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data)
{
    int vals[2] = {stream->args[0], stream->args[1]};

    HIDE_UNUSED_PTR(virtual_memory);
    HIDE_UNUSED_PTR(global_data);
    if (!IS_A_REG_ID(stream->args[2]))
        return EPITECH_FAILURE;
    if (IS_REG(stream->types[0])) {
        if (!IS_A_REG_ID(vals[0]))
            return EPITECH_FAILURE;
        vals[0] = stream->registers[vals[0] - 1];
    } else if (IS_INDIR(stream->types[0]))
        vals[0] += stream->pos;
    if (IS_REG(stream->types[1])) {
        if (!IS_A_REG_ID(vals[1]))
            return EPITECH_FAILURE;
        vals[1] = stream->registers[vals[1] - 1];
    } else if (IS_INDIR(stream->types[1]))
        vals[1] += stream->pos;
    stream->registers[stream->args[2] - 1] = vals[0] & vals[1];
    return EPITECH_SUCCESS;
}

int or_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data)
{
    int vals[2] = {stream->args[0], stream->args[1]};

    HIDE_UNUSED_PTR(virtual_memory);
    HIDE_UNUSED_PTR(global_data);
    if (!IS_A_REG_ID(stream->args[2]))
        return EPITECH_FAILURE;
    if (IS_REG(stream->types[0])) {
        if (!IS_A_REG_ID(vals[0]))
            return EPITECH_FAILURE;
        vals[0] = stream->registers[vals[0] - 1];
    } else if (IS_INDIR(stream->types[0]))
        vals[0] += stream->pos;
    if (IS_REG(stream->types[1])) {
        if (!IS_A_REG_ID(vals[1]))
            return EPITECH_FAILURE;
        vals[1] = stream->registers[vals[1] - 1];
    } else if (IS_INDIR(stream->types[1]))
        vals[1] += stream->pos;
    stream->registers[stream->args[2] - 1] = vals[0] | vals[1];
    return EPITECH_SUCCESS;
}

int xor_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data)
{
    int vals[2] = {stream->args[0], stream->args[1]};

    HIDE_UNUSED_PTR(virtual_memory);
    HIDE_UNUSED_PTR(global_data);
    if (!IS_A_REG_ID(stream->args[2]))
        return EPITECH_FAILURE;
    if (IS_REG(stream->types[0])) {
        if (!IS_A_REG_ID(vals[0]))
            return EPITECH_FAILURE;
        vals[0] = stream->registers[vals[0] - 1];
    } else if (IS_INDIR(stream->types[0]))
        vals[0] += stream->pos;
    if (IS_REG(stream->types[1])) {
        if (!IS_A_REG_ID(vals[1]))
            return EPITECH_FAILURE;
        vals[1] = stream->registers[vals[1] - 1];
    } else if (IS_INDIR(stream->types[1]))
        vals[1] += stream->pos;
    stream->registers[stream->args[2] - 1] = vals[0] ^ vals[1];
    return EPITECH_SUCCESS;
}
