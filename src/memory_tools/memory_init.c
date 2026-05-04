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

static int read_header(exec_stream_t *stream, FILE *file)
{
    int magic = 0;
    char padding[3] = {0, 0, 0};

    if (fread(&magic, sizeof(int), 1, file) != sizeof(int))
        return EPITECH_FAILURE;
    if (__bswap_32(magic) != COREWAR_EXEC_MAGIC)
        return EPITECH_FAILURE;
    if (fread(stream->prog_name, sizeof(char), PROG_NAME_LENGTH, file) !=
        PROG_NAME_LENGTH)
        return EPITECH_FAILURE;
    if (fread(padding, sizeof(char), 3, file) != 3)
        return EPITECH_FAILURE;
    if (fread(&(stream->prog_size), sizeof(int), 1, file) != sizeof(int))
        return EPITECH_FAILURE;
    stream->prog_size = __bswap_32(stream->prog_size);
    if (fread(stream->comment, sizeof(char), COMMENT_LENGTH, file) !=
        COMMENT_LENGTH)
        return EPITECH_FAILURE;
    return EPITECH_SUCCESS;
}

static exec_stream_t load_the_champion(byte_t *virtual_memory,
    const char *filename, int alloc_size, size_t pos)
{
    exec_stream_t stream = null_stream;
    FILE *file = fopen(filename, "rb");
    size_t size_to_read = alloc_size;

    if (file == NULL)
        return stream;
    if (read_header(&stream, file) != EPITECH_SUCCESS) {
        fclose(file);
        return stream;
    }
    if (stream.prog_size < alloc_size)
        size_to_read = stream.prog_size;
    if (fread(&(virtual_memory[pos]), sizeof(byte_t), size_to_read, file) !=
        size_to_read) {
        fclose(file);
        return stream;
    }
    fclose(file);
    stream.pos = pos;
    return stream;
}

static exec_stream_t *load_champions_in_virt_mem(byte_t *virtual_memory,
    int champions_nbr, const char **filenames)
{
    size_t alloc_size = MEM_SIZE / champions_nbr;
    exec_stream_t *streams = my_calloc(sizeof(exec_stream_t) *
        (champions_nbr + 1));

    streams[champions_nbr].pos = -1;
    for (int i = 0; i < champions_nbr; ++i) {
        streams[i] = load_the_champion(virtual_memory, filenames[i], alloc_size,
            alloc_size * i);
        if (streams[i].pos < 0) {
            free(streams);
            return NULL;
        }
    }
    return streams;
}

int init_memory(int champions_nbr, const char **file_names,
    byte_t **virtual_memory_ptr, exec_stream_t **streams_ptr)
{
    *virtual_memory_ptr = my_calloc(sizeof(byte_t) * MEM_SIZE);
    if (*virtual_memory_ptr == NULL)
        return EPITECH_FAILURE;
    *streams_ptr = load_champions_in_virt_mem(*virtual_memory_ptr,
        champions_nbr, file_names);
    if (*streams_ptr == NULL) {
        free(*virtual_memory_ptr);
        *virtual_memory_ptr = NULL;
        return EPITECH_FAILURE;
    }
    return EPITECH_SUCCESS;
}
