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
    #define PADDING_SIZE 3

    #define HIDE_UNUSED_PTR(ptr) (ptr = &(ptr[0]))

    // dump
    #define NBR_COLUMNS 32

int corewar(int champions_nbr, const char **filenames);

// parsing
void set_champions_id(champion_t *champions, size_t ch_nbr);
void set_champions_load_address(champion_t *champions, size_t ch_nbr);
champion_t *parse_arguments(const int ac, const char **av, size_t *ch_nbr,
    long *dump_value);

// dump
void dump_vm(byte_t *virtual_memory, global_data_t *global_data);

// execution
// void execute_tick(byte_t *virtual_memory, global_data_t *global_data);
int execute_instruction(byte_t *virtual_memory, size_t stream_index,
    global_data_t *global_data);
void execute_tick(byte_t *virtual_memory, global_data_t *global_data);

// memory tools
int print_error(const char *prefix, const char *msg);
// int init_memory(int champions_nbr, const char **file_names,
//     byte_t **virtual_memory_ptr, prog_stream_t **streams_ptr);
byte_t *init_memory(const int ac, const char **av, global_data_t *global_data);
int read_byte(byte_t *virtual_memory, size_t position);
int read_indirect_or_index(byte_t *virtual_memory, size_t position);
int read_direct(byte_t *virtual_memory, size_t position);
void write_byte(byte_t *virtual_memory, size_t position, byte_t value);
void write_indirect_or_index(byte_t *virtual_memory, size_t position,
    short value);
void write_direct(byte_t *virtual_memory, size_t position, int value);
void memory_copy(byte_t *virtual_memory, size_t src_pos, size_t dest_pos,
    size_t n);
void memory_clear(byte_t *virtual_memory, size_t pos, size_t n);

#endif /* STREAM_ */
