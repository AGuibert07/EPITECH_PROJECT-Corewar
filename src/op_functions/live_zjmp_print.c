/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains live, zjmp and print instruction functions
*/

#include "mem.h"
#include "my.h"

int live_instruction(byte_t *virtual_memory, exec_stream_t *stream,
    global_data_t *global_data)
{
    global_data->lives[stream->champion_id - 1] = 0;
    return EPITECH_SUCCESS;
}

int zjmp_instruction(byte_t *virtual_memory, exec_stream_t *stream,
    global_data_t *global_data)
{
    if (stream->args[0] > 0)
        stream->curent_byte = stream->args[0];
    return EPITECH_SUCCESS;
}

int print_instruction(byte_t *virtual_memory, exec_stream_t *stream,
    global_data_t *global_data)
{
    if (!IS_A_REG_ID(stream->args[0]))
        return EPITECH_FAILURE;
    my_putchar(stream->registers[stream->args[0] - 1] % _2_POW_8);
    return EPITECH_SUCCESS;
}
