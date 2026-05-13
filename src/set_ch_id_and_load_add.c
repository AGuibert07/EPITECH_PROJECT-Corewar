/*
** EPITECH PROJECT, 2026
** G2 - Elementary Programming in C - Corewar
** File description:
** main file of the project
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "mem.h"
#include "my.h"

static bool is_in_int_arr(size_t *arr, size_t size, size_t val)
{
    for (size_t i = 0; i < size; ++i)
        if (arr[i] == val)
            return true;
    return false;
}

static size_t get_next_free_id(size_t *arr, size_t size, size_t pos)
{
    size_t max = 0;

    for (size_t i = 0; i < pos; ++i)
        if (arr[i] > max)
            max = arr[i];
    max += 1;
    while (max < __INT64_MAX__ && is_in_int_arr(arr, size, max))
        max += 1;
    return max;
}

void set_champions_id(champion_t *champions, size_t ch_nbr)
{
    size_t ch_id[ch_nbr];

    for (size_t i = 0; i < ch_nbr; ++i) {
        if (is_in_int_arr(ch_id, i, champions[i].champion_id)) {
            ch_id[i] = 0;
            champions[i].champion_id = 0;
        } else
            ch_id[i] = champions[i].champion_id;
    }
    for (size_t i = 0; i < ch_nbr; ++i)
        if (ch_id[i] == 0)
            ch_id[i] = get_next_free_id(ch_id, ch_nbr, i);
    for (size_t i = 0; i < ch_nbr; ++i)
        champions[i].champion_id = ch_id[i];
}

static size_t get_next_ch_with_set_load_add(champion_t *champions,
    size_t start_pos, bool use_start_pos_if_nf)
{
    size_t i = start_pos;

    while (champions[i].filename) {
        if (champions[i].load_address >= 0)
            return i;
        i += 1;
    }
    if (use_start_pos_if_nf) {
        champions[start_pos].load_address = 0;
        return start_pos;
    }
    return i;
}

void set_champions_load_address(champion_t *champions, size_t ch_nbr)
{
    size_t departure_point = get_next_ch_with_set_load_add(champions, 0, true);
    size_t bounds[2] = {departure_point, departure_point + 1};
    size_t space = 0;
    int range = 0;

    if (ch_nbr <= 1)
        return;
    while (bounds[1] != departure_point) {
        bounds[1] =
            get_next_ch_with_set_load_add(champions, bounds[0] + 1, false);
        if (bounds[1] >= ch_nbr)
            bounds[1] = departure_point;
        range = ((bounds[1] + ch_nbr) - bounds[0]) % (ch_nbr + 1);
        space = (((champions[bounds[1]].load_address + MEM_SIZE) -
                champions[bounds[0]].load_address) % (MEM_SIZE + 1)) / range;
        for (int i = 1; i < range; ++i)
            champions[(bounds[0] + i)].load_address =
                (champions[bounds[0]].load_address + (space * i)) % MEM_SIZE;
        bounds[0] = bounds[1];
    }
}
