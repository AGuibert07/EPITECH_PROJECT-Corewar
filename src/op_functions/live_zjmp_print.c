/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains live, zjmp and print instruction functions
*/

#include "mem.h"
#include "my.h"

int live_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data)
{
    int tmp = 0;

    HIDE_UNUSED_PTR(virtual_memory);
    for (size_t i = 0; global_data->champions[i].filename != NULL; ++i) {
        tmp = global_data->champions[i].champion_id;
        if (tmp == stream->args[0]) {
            global_data->champions[i].live = 0;
            my_putstr("live: ");
            my_putstr((const char *)(global_data->champions[i].prog_name));
            my_putchar('\n');
        }
    }
    return EPITECH_SUCCESS;
}

int zjmp_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data)
{
    HIDE_UNUSED_PTR(virtual_memory);
    HIDE_UNUSED_PTR(global_data);
    if (stream->args[0] > 0)
        stream->curent_byte = stream->args[0];
    return EPITECH_SUCCESS;
}

int print_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data)
{
    HIDE_UNUSED_PTR(virtual_memory);
    HIDE_UNUSED_PTR(global_data);
    if (!IS_A_REG_ID(stream->args[0]))
        return EPITECH_FAILURE;
    my_putchar(stream->registers[stream->args[0] - 1] % _2_POW_8);
    return EPITECH_SUCCESS;
}
