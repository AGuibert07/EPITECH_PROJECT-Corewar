/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** Header for the operations
*/

#ifndef OP_H_
    #define OP_H_

    #include <stdio.h>
    #include <stdbool.h>
    #include "asm.h"

    #define MEM_SIZE (6 * 1024)
    #define IDX_MOD 512 /* modulo of the index < */

    #define COMMENT_CHAR '#'
    #define LABEL_CHAR ':'
    #define DIRECT_CHAR '%'
    #define SEPARATOR_CHAR ','
    #define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

    #define NAME_CMD_STRING ".name"
    #define COMMENT_CMD_STRING ".comment"

    #define PACKED_ATTR __attribute__((packed))

/*
** size (in bytes)
*/
    #define IND_SIZE 2
    #define DIR_SIZE 4
    #define REG_SIZE DIR_SIZE

    #define _TYPES ((int[]){0, 1, 3, 0, 2})
    #define T_TO_CB(t) (_TYPES[t % T_LAB])
    #define _DIR_AS_IND(t) ((t & (T_DIR | T_INDEX)) == (T_DIR | T_INDEX))
    #define SIZE_O(t) ((_DIR_AS_IND(t)) ? (IND_SIZE) : (t & T_ALL))
    // #define SIZE_OF_TYPE(t) (((t & T_INDEX) == 0) ? (t & T_ALL) : (IND_SIZE))

// instruction functions
int live_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
int ld_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
int st_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
int add_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
int sub_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
int and_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
int or_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
int xor_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
int zjmp_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
int ldi_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
int sti_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
int fork_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
int lld_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
int lldi_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
int lfork_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
int print_instruction(byte_t *virtual_memory, prog_stream_t *stream,
    global_data_t *global_data);
// op_tab
static const op_t op_tab[] = {
    {"none", 0, {0}, 0, false, 1, "Nothing", 0},
    {"live", 1, {T_DIR}, 1, false, 10, "alive",
        (op_function_t)(&live_instruction)},
    {"ld", 2, {T_DIR | T_IND, T_REG}, 2, true, 5, "load",
        (op_function_t)(&ld_instruction)},
    {"st", 2, {T_REG, T_REG | T_IND}, 3, true, 5, "store",
        (op_function_t)(&st_instruction)},
    {"add", 3, {T_REG, T_REG, T_REG}, 4, true, 10, "addition",
        (op_function_t)(&add_instruction)},
    {"sub", 3, {T_REG, T_REG, T_REG}, 5, true, 10, "subtraction",
        (op_function_t)(&sub_instruction)},
    {"and", 3, {T_ALL, T_ALL, T_REG}, 6, true, 6,
        "binary and (and  r1, r2, r3   r1&r2 -> r3",
        (op_function_t)(&and_instruction)},
    {"or", 3, {T_ALL, T_ALL, T_REG}, 7, true, 6,
        "binary or  (or   r1, r2, r3   r1 | r2 -> r3",
        (op_function_t)(&or_instruction)},
    {"xor", 3, {T_ALL, T_ALL, T_REG}, 8, true, 6,
        "binary exclusive or (xor  r1, r2, r3   r1^r2 -> r3",
        (op_function_t)(&xor_instruction)},
    {"zjmp", 1, {T_DIR | T_INDEX}, 9, false, 20, "jump if zero",
        (op_function_t)(&zjmp_instruction)},
    {"ldi", 3, {T_ALL | T_INDEX, T_REG | T_DIR, T_REG | T_INDEX}, 10, true, 25,
        "load indirect", (op_function_t)(&ldi_instruction)},
    {"sti", 3, {T_REG, T_ALL | T_INDEX, T_REG | T_DIR | T_INDEX}, 11, true, 25,
        "store indirect", (op_function_t)(&sti_instruction)},
    {"fork", 1, {T_DIR | T_INDEX}, 12, false, 800, "fork",
        (op_function_t)(&fork_instruction)},
    {"lld", 2, {T_DIR | T_IND, T_REG}, 13, true, 10, "long load",
        (op_function_t)(&lld_instruction)},
    {"lldi", 3, {T_ALL | T_INDEX, T_REG | T_DIR | T_INDEX, T_REG}, 14, true, 50,
        "long load indirect", (op_function_t)(&lldi_instruction)},
    {"lfork", 1, {T_DIR | T_INDEX}, 15, false, 1000, "long fork",
        (op_function_t)(&lfork_instruction)},
    {"print", 1, {T_REG}, 16, true, 2, "print character",
        (op_function_t)(&print_instruction)},
    null_op
};

    // live
    #define CYCLE_TO_DIE 1536 /* number of cycle before beig declared dead */
    #define CYCLE_DELTA 5
    #define NBR_LIVE 40


    // print arguments functions
typedef int (*print_arg_func_t)(FILE *file, instruction_t *inst,
    const unsigned int index, label_t *labels);

struct print_arg_s {
    args_type_t type;
    print_arg_func_t funct;
} typedef print_arg_t;

#endif /* OP_H_ */
