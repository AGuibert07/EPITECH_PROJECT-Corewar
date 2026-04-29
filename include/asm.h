/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** main header file of the project
*/

#ifndef ASM_
    #define ASM_

    #include <stdbool.h>

    #define FILE_EXTENSION "s"
    #define REVERSE_BYTES must_bytes_be_inverted()

    #define MAX_ARGS_NUMBER 4 /* this may not be changed 2^*IND_SIZE */

    #define BYTE_MAX 255

    // args types
enum args_type_e {
    T_REG = 1,      // register
    T_DIR = 4,      // direct  (ld  #1,r1  put 1 into r1)
    T_IND = 2,      /* indirect always relative (ld 1,r1 put what's in the
                    address (1+pc) into r1 (4 bytes )) */
    T_ALL = (T_REG | T_DIR | T_IND),  // any type of argument
    T_INDEX = 8     /* for index argument (that will always be written as
                        indirect) */
} typedef args_type_t;

typedef char byte_t;

typedef struct op_s {
    char *mnemonique;
    char nbr_args;
    byte_t type[MAX_ARGS_NUMBER];
    char code;
    bool coding_byte;
    int nbr_cycles;
    char *comment;
} op_t;

struct instruction_s {
    op_t op;
    char *args[MAX_ARGS_NUMBER + 1];
    args_type_t types[MAX_ARGS_NUMBER];
    char size;
} typedef instruction_t;

struct label_s {
    char *label;
    short id;
    int pos;
    struct label_s *next;
} typedef label_t;

#endif /* ASM_ */
