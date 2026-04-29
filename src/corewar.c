/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains the corewar functions
*/

#include <stdbool.h>
#include "stream.h"
#include "my.h"

int execute_tick(byte_t *virtual_memory, exec_stream_t *streams)
{
    for (size_t i = 0; streams[i].pos >= 0; ++i) {
        if (streams->inst_time > 0)
            streams->inst_time -= 1;
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
