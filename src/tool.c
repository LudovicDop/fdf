#include "../include/mlx.h"

void    free_my_tab(char ***tab)
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
            printf("tab[%d][%d]\n",i, j);
            free(tab[i][j]);
            j++;
        }
        printf("tab[%d]\n",i);
        free(tab[i]);
        i++;
    }
    free(tab);
    tab = NULL;
}