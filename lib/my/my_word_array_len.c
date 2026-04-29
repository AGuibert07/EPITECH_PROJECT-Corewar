/*
** EPITECH PROJECT, 2026
** libmy.a
** File description:
** this file countains the my_word_array_len function
*/

int my_word_array_len(char const **tab)
{
    int l = 0;

    if (tab == 0)
        return -1;
    while (tab[l] != 0)
        l += 1;
    return l;
}
