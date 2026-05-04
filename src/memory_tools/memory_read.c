/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains all functions to read from the virtual memory
*/

#include <stdio.h>
#include <sys/stat.h>
#include <byteswap.h>
#include <stdlib.h>
#include "mem.h"
#include "op.h"
#include "my.h"

int read_byte(byte_t *virtual_memory, size_t position)
{
    int byte = virtual_memory[position % MEM_SIZE];

    return byte;
}

int read_indirect_or_index(byte_t *virtual_memory, size_t position)
{
    return read_byte(virtual_memory, position) +
        read_byte(virtual_memory, position + sizeof(byte_t)) * _2_POW_8;
}

int read_direct(byte_t *virtual_memory, size_t position)
{
    int dir_val = read_indirect_or_index(virtual_memory, position) +
        read_indirect_or_index(virtual_memory, position + T_IND) *
        _2_POW_8 * _2_POW_8;

    return dir_val;
}
