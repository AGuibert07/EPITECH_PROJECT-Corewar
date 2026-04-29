/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains the live instruction function
*/

#include "mem.h"
#include "my.h"

int live_instruction(byte_t *virtual_memory, exec_stream_t *stream,
    global_data_t *global_data)
{
    global_data->lives[stream->champion_id - 1] = 0;
    return EPITECH_SUCCESS;
}
