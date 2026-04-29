/*
** EPITECH PROJECT, 2026
** libmy.a
** File description:
** this file countains all free array functions
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void free_array(void **arr, unsigned int dim_nbr)
{
    if (arr == NULL)
        return;
    if (dim_nbr < 1)
        return;
    if (dim_nbr == 1) {
        free(arr);
        return;
    }
    for (int i = 0; arr[i] != NULL; ++i)
        free_array(arr[i], dim_nbr - 1);
    free(arr);
}

void sfree_array(void **arr, unsigned int size)
{
    if (arr == NULL)
        return;
    for (unsigned int i = 0; i < size; ++i)
        if (arr[i] != NULL)
            free(arr[i]);
    free(arr);
}

void nfree(unsigned int n, ...)
{
    va_list list;
    void *ptr = NULL;

    va_start(list, n);
    for (unsigned int i = 0; i < n; ++i) {
        ptr = va_arg(list, void *);
        if (ptr != NULL)
            free(ptr);
    }
    va_end(list);
}

void nfree_array(unsigned int dim_nbr, unsigned int n, ...)
{
    va_list list;
    void *ptr;

    va_start(list, n);
    for (unsigned int i = 0; i < n; ++i) {
        ptr = va_arg(list, void *);
        if (ptr != NULL) {
            free_array(ptr, dim_nbr);
        }
    }
    va_end(list);
}
