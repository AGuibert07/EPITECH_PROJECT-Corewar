/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** main header file of the project
*/

#ifndef STREAM_
    #define STREAM_

    #include <stddef.h>
    #include <stdbool.h>
    #include "op.h"

    #define MIN_CHAMPIONS_NBR 2
    #define MAX_CHAMPIONS_NBR 4
    #define _2_POW_8 256

struct exec_stream_s {
    byte_t champion_id;
    char prog_name[PROG_NAME_LENGTH + 1];
    char comment[COMMENT_LENGTH + 1];
    int prog_size;
    int pos;
    int inst_time;
    op_t instruction;
} typedef exec_stream_t;

int init_memory(int champions_nbr, const char **file_names,
    byte_t **virtual_memory_ptr, exec_stream_t **streams_ptr);

// memory tools
int read_byte(byte_t *virtual_memory, size_t position);
int read_indirect_or_index(byte_t *virtual_memory, size_t position);
int read_direct(byte_t *virtual_memory, size_t position);
void write_byte(byte_t *virtual_memory, size_t position, byte_t value);
int write_indirect_or_index(byte_t *virtual_memory, size_t position,
    short value);
int write_direct(byte_t *virtual_memory, size_t position, int value);
void memory_copy(byte_t *virtual_memory, size_t src_pos, size_t dest_pos,
    size_t n);
void memory_clear(byte_t *virtual_memory, size_t pos, size_t n);

#endif /* STREAM_ */
