#include "../include/mlx.h"

void free_my_tab_2d(char **tab)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (tab[i])
    {
        j = 0;
        while(tab[i][j])
        {
            free(tab[i]);
            j++;
        }
        i++;
    }
    free(tab);
}