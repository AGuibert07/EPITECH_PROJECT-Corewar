/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** this file contains all functions to write to the virtual memory
*/

#include <stdio.h>
#include <sys/stat.h>
#include <byteswap.h>
#include <stdlib.h>
#include "mem.h"
#include "op.h"
#include "my.h"

void memory_copy(byte_t *virtual_memory, size_t src_pos, size_t dest_pos,
    size_t n)
{
    for (size_t i = 0; i < n; ++i)
        virtual_memory[(dest_pos + i) % MEM_SIZE] =
            virtual_memory[(src_pos + i)];
}

void memory_clear(byte_t *virtual_memory, size_t pos, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        virtual_memory[(pos + i) % MEM_SIZE] = 0;
}
