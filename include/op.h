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
** regs
*/
    #define REG_NUMBER 16 /* r1 <--> rx */

/*
** size (in bytes)
*/
    #define IND_SIZE 2
    #define DIR_SIZE 4
    #define REG_SIZE 1

    #define _TYPES ((int[]){0, 1, 3, 0, 2})
    #define T_TO_CB(t) (_TYPES[t % T_LAB])
    #define _DIR_AS_IND(t) ((t & (T_DIR | T_INDEX)) == (T_DIR | T_INDEX))
    #define SIZE_O(t) ((_DIR_AS_IND(t)) ? (IND_SIZE) : (t & T_ALL))
    // #define SIZE_OF_TYPE(t) (((t & T_INDEX) == 0) ? (t & T_ALL) : (IND_SIZE))

/*
** op_tab
*/
static const op_t op_tab[] = {
    {"none", 0, {0}, 0, false, 1, "Nothing"},
    {"live", 1, {T_DIR}, 1, false, 10, "alive"},
    {"ld", 2, {T_DIR | T_IND, T_REG}, 2, true, 5, "load"},
    {"st", 2, {T_REG, T_REG | T_IND}, 3, true, 5, "store"},
    {"add", 3, {T_REG, T_REG, T_REG}, 4, true, 10, "addition"},
    {"sub", 3, {T_REG, T_REG, T_REG}, 5, true, 10, "subtraction"},
    {"and", 3, {T_ALL, T_ALL, T_REG}, 6, true, 6,
        "binary and (and  r1, r2, r3   r1&r2 -> r3"},
    {"or", 3, {T_ALL, T_ALL, T_REG}, 7, true, 6,
        "binary or  (or   r1, r2, r3   r1 | r2 -> r3"},
    {"xor", 3, {T_ALL, T_ALL, T_REG}, 8, true, 6,
        "binary exclusive or (xor  r1, r2, r3   r1^r2 -> r3"},
    {"zjmp", 1, {T_DIR | T_INDEX}, 9, false, 20, "jump if zero"},
    {"ldi", 3, {T_ALL | T_INDEX, T_REG | T_DIR, T_REG | T_INDEX}, 10, true, 25,
        "load indirect"},
    {"sti", 3, {T_REG, T_ALL | T_INDEX,
            T_REG | T_DIR | T_INDEX}, 11, true, 25, "store indirect"},
    {"fork", 1, {T_DIR | T_INDEX}, 12, false, 800, "fork"},
    {"lld", 2, {T_DIR | T_IND, T_REG}, 13, true, 10, "long load"},
    {"lldi", 3, {T_ALL | T_INDEX, T_REG | T_DIR | T_INDEX, T_REG}, 14, true, 50,
        "long load indirect"}, // ?
    {"lfork", 1, {T_DIR | T_INDEX}, 15, false, 1000, "long fork"},
    {"print", 1, {T_REG}, 16, true, 2, "print character"},
    {0, 0, {0}, 0, false, -1, 0, 0}
};

/*
** header
*/
    #define PROG_NAME_LENGTH 128
    #define COMMENT_LENGTH 2048
    #define COREWAR_EXEC_MAGIC 0xea83f3

typedef struct header_s {
    int magic;
    char prog_name[PROG_NAME_LENGTH + 1];
    char padding[3];
    int prog_size;
    char comment[COMMENT_LENGTH + 1];
    char padding2[3];
} header_t;

/*
** live
*/
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
