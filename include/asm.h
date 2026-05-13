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

    // header
    #define PROG_NAME_LENGTH 128
    #define COMMENT_LENGTH 2048
    #define COREWAR_EXEC_MAGIC 0xea83f3

    // regs
    #define REG_NUMBER 16 /* r1 <--> rx */
    #define IS_A_REG_ID(n) (n > 0 && n <= REG_NUMBER)

    // args types
enum args_type_e {
    T_NONE = 0,     // none type
    T_REG = 1,      // register
    T_DIR = 4,      // direct  (ld  #1,r1  put 1 into r1)
    T_IND = 2,      /* indirect always relative (ld 1,r1 put what's in the
                    address (1+pc) into r1 (4 bytes )) */
    T_ALL = (T_REG | T_DIR | T_IND),  // any type of argument
    T_INDEX = 8     /* for index argument (that will always be written as
                        indirect) */
} typedef args_type_t;

    #define IS_REG(t) ((t & T_REG) == T_REG)
    #define IS_DIR(t) ((t & T_DIR) == T_DIR)
    #define IS_INDIR(t) ((t & T_IND) == T_IND)
    #define IS_INDEX(t) ((t & T_INDEX) == T_INDEX)

typedef char byte_t;

typedef int (*op_function_t)(byte_t *, void *, void *);

typedef struct op_s {
    char *mnemonique;
    char nbr_args;
    byte_t type[MAX_ARGS_NUMBER];
    char code;
    bool coding_byte;
    int nbr_cycles;
    char *comment;
    op_function_t op_function;
} op_t;

static const op_t null_op = {NULL, 0, {0}, 0, false, -1, NULL, NULL};

struct champion_s {
    size_t champion_id;
    char *filename;
    char prog_name[PROG_NAME_LENGTH + 1];
    char comment[COMMENT_LENGTH + 1];
    size_t prog_size;
    size_t live;
    bool alive;
    int load_address;
    size_t time_death;
} typedef champion_t;

static const champion_t null_champion = {0, NULL, {0}, {0}, 0, 0, false, -1, 0};

struct prog_stream_s {
    champion_t *champion_data;
    int registers[REG_NUMBER];
    size_t pos;
    size_t curent_byte;
    size_t nbr_cycles;
    op_t op;
    args_type_t types[MAX_ARGS_NUMBER + 1];
    int args[MAX_ARGS_NUMBER + 1];
    bool running;
    int carry;
} typedef prog_stream_t;

static const prog_stream_t null_stream =
    {NULL, {0}, 0, 0, 0, null_op, {T_NONE}, {0}, true, 0};

// struct exec_stream_s {
//     byte_t champion_id;
//     char prog_name[PROG_NAME_LENGTH + 1];
//     char comment[COMMENT_LENGTH + 1];
//     int prog_size;
//     int registers[REG_NUMBER];
//     int pos;
//     int curent_byte;
//     int inst_time;
//     op_t instruction;
//     args_type_t types[MAX_ARGS_NUMBER + 1];
//     int args[MAX_ARGS_NUMBER + 1];
//     bool running;
// } typedef exec_stream_t;

// static const exec_stream_t null_stream = {0, {0}, {0}, 0, {0}, -1, 0, -1,
//     null_op, {0}, {0}, true};

struct global_data_s {
    size_t champions_nbr;
    size_t alive_champions_nbr;
    size_t lives[MAX_ARGS_NUMBER];
    champion_t *champions;
    prog_stream_t *streams;
    size_t progs_nbr;
    long int dump_val;
    size_t cycles;
} typedef global_data_t;

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
