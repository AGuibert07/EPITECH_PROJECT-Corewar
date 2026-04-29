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
#include "stream.h"
#include "op.h"
#include "my.h"

void write_byte(byte_t *virtual_memory, size_t position, byte_t value) {
    virtual_memory[position % MEM_SIZE] = value;
}

int write_indirect_or_index(byte_t *virtual_memory, size_t position,
    short value) {
    write_byte(virtual_memory, position, value % _2_POW_8);
    write_byte(virtual_memory, position + sizeof(byte_t),
        value >> __CHAR_BIT__);
}

int write_direct(byte_t *virtual_memory, size_t position, int value) {
    write_indirect_or_index(virtual_memory, position,
        value % (_2_POW_8 * _2_POW_8));
    write_indirect_or_index(virtual_memory, position + T_IND,
        value >> (__CHAR_BIT__ * T_IND));
}
