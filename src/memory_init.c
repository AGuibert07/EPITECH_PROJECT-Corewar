/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** main file of the project
*/

#include <stdlib.h>
#include <stdio.h>
#include <byteswap.h>
#include "mem.h"
#include "my.h"

int print_error(const char *prefix, const char *msg)
{
    if (prefix != NULL) {
        my_putstr_error(prefix);
        my_putstr_error(": ");
    }
    my_putstr_error(msg);
    my_putchar_error('\n');
    return EPITECH_FAILURE;
}

static bool read_padding(FILE *file)
{
    char padding[PADDING_SIZE] = {0};

    return (fread(padding, sizeof(char), PADDING_SIZE, file) == PADDING_SIZE);
}

static bool read_int(FILE *file, int *ptr)
{
    if (fread(ptr, sizeof(int), 1, file) != 1)
        return false;
    *ptr = __bswap_32(*ptr);
    return true;
}

static bool read_str(FILE *file, char *ptr, size_t size)
{
    return (fread(ptr, sizeof(char), size, file) == size);
}

static int read_header(champion_t *champion, FILE *file)
{
    int tmp = 0;

    if (!read_int(file, &tmp))
        return EPITECH_FAILURE;
    if (tmp != COREWAR_EXEC_MAGIC)
        return print_error(champion->filename,
            "Invalid champion binary file (invalid magic).");
    if (!read_str(file, champion->prog_name, PROG_NAME_LENGTH) ||
        !read_padding(file) || !read_int(file, &tmp))
        return EPITECH_FAILURE;
    champion->prog_size = tmp;
    if (!read_str(file, champion->comment, COMMENT_LENGTH) ||
        !read_padding(file))
        return EPITECH_FAILURE;
    return EPITECH_SUCCESS;
}

static int load_the_champion(byte_t *virtual_memory, champion_t *champion,
    prog_stream_t *stream, size_t alloc_size)
{
    FILE *file = fopen(champion->filename, "rb");
    size_t size_to_read = alloc_size;

    *stream = null_stream;
    if (file == NULL)
        return print_error(champion->filename, "Can't open the file.");
    if (read_header(champion, file) != EPITECH_SUCCESS) {
        fclose(file);
        return EPITECH_FAILURE;
    }
    if (champion->prog_size < alloc_size)
        size_to_read = champion->prog_size;
    if (fread(&(virtual_memory[champion->load_address]), sizeof(byte_t),
            size_to_read, file) != size_to_read) {
        fclose(file);
        return EPITECH_FAILURE;
    }
    fclose(file);
    return EPITECH_SUCCESS;
}

static int load_champions_in_virt_mem(byte_t *virtual_memory,
    global_data_t *global_data)
{
    size_t alloc_size = 0;

    if (global_data == NULL)
        return EPITECH_FAILURE;
    if (global_data->champions == NULL || global_data->streams == NULL)
        return EPITECH_FAILURE;
    for (size_t i = 0; i < global_data->champions_nbr; ++i) {
        alloc_size = MEM_SIZE;
        if (global_data->champions[i + 1].filename != NULL)
            alloc_size = global_data->champions[i + 1].load_address;
        alloc_size -= global_data->champions[i].load_address;
        if (load_the_champion(virtual_memory, &(global_data->champions[i]),
                &(global_data->streams[i]), alloc_size) != EPITECH_SUCCESS)
            return EPITECH_FAILURE;
    }
    return EPITECH_SUCCESS;
}

byte_t *init_memory(const int ac, const char **av, global_data_t *global_data)
{
    byte_t *virtual_memory = my_calloc(sizeof(byte_t) * MEM_SIZE);

    if (virtual_memory == NULL)
        return NULL;
    global_data->champions = parse_arguments(ac, av,
        &(global_data->champions_nbr), &(global_data->dump_val));
    global_data->alive_champions_nbr = global_data->champions_nbr;
    if (global_data->champions == NULL) {
        free(virtual_memory);
        return NULL;
    }
    global_data->streams = my_calloc(sizeof(prog_stream_t) *
        (global_data->champions_nbr + 1));
    if (global_data->streams == NULL ||
        load_champions_in_virt_mem(virtual_memory, global_data) !=
        EPITECH_SUCCESS) {
        nfree(2, virtual_memory, global_data->champions);
        return NULL;
    }
    return virtual_memory;
}
