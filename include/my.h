/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Robot Factory - Alexis & Antoine
** File description:
** this header file countains all libmy function declarations
*/

#ifndef MY_
    #define MY_

    #include <stdio.h>
    #include <stdbool.h>

    #define SIGN(n) ((n < 0) ? (-1) : (1))
    #define ABS(n) ((n < 0) ? (-n) : (n))

    #define DIGITS "0123456789"
    #define BIN_DIGITS "01"
    #define UP_HEXA_DIGITS "0123456789ABCDEF"
    #define LOW_HEXA_DIGITS "0123456789abcdef"
    #define UP_LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    #define LOW_LETTERS "abcdefghijklmnopqrstuvwxyz"
    #define LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

enum epitech_output {
    EPITECH_SUCCESS = 0,
    EPITECH_FAILURE = 84
} typedef epitech_output_t;

void free_array(void **arr, unsigned int dim_nbr);
char **get_file_content(char *filename);
int get_file_size(char *filename);
void *my_calloc(size_t size);
int my_compute_power_rec(int nb, int p);
int my_getnbr(char const *str);
int my_index_of_str(char c, char *str);
int my_index_of_word_array(char *str, char **arr);
char *my_int_to_str_function(long long int nbr, const char *base);
bool my_is_in_str(char c, char *str);
bool my_is_in_word_array(char *str, char **arr);
int my_nbr_occurences_in_str(char c, char *str);
void my_putchar(char c);
void my_putchar_error(char c);
void my_put_nbr(long long int nb);
void my_put_nbr_error(int nb);
void my_putstr(char const *str);
void my_putstr_error(char const *str);
void my_replace_in_str(char *str, char c, char c_new);
void my_show_word_array(char const **tab);
char **my_split_str(char *str, const char *sep);
int my_strcmp(char const *s1, char const *s2);
char *my_str_concat(char *str1, char *str2);
char *my_strdup(char const *str);
char **my_string_arr_dup(char **arr);
bool my_str_isnbr(char const *str);
bool my_str_isnum(char const *str);
char *my_str_join(const char *separator, const char **arr);
int my_strlen(char const *str);
char *my_str_n_concat(unsigned int n, ...);
char *my_substring(char *str, int start_pos, unsigned int n);
char **my_word_array_concat(char **arr1, char **arr2);
int my_word_array_len(char const **tab);
void nfree(unsigned int n, ...);
void nfree_array(unsigned int dim_nbr, unsigned int n, ...);
void sfree_array(void **arr, unsigned int size);
char **read_file(FILE *file, int buffer_size);

#endif /* MY_ */
