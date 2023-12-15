/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_for_mlx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:03:56 by ldoppler          #+#    #+#             */
/*   Updated: 2023/12/15 17:18:27 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>

static int how_many_split(char *string)
{
    int i;
    int k;

    k = 0;
    i = 0;
    while (string[i])
    {
        if (string[i] != ' ' && string[i] != '\n' && string[i])
        {
            printf("string[%d] = %c\n",i,string[i]);
            k++;
            while (string[i] != ' ' && string[i] != '\n' && string[i])
                i++;
        }
            i++;
    }
    return (k);
}

static char **implement(char *string, char **ret)
{
    
}

static int  each_word_memory(char *string, char **ret)
{
    int i;
    int k;
    int j;
    int o;
    
    j = 0;
    k = 0;
    k = 0;
    i = 0;
    while (string[i])
    {
        k = 0;
        while (string[i] != ' ' && string[i] != '\n')
        {
            k++;
            i++;
        }
        printf("Each word : %d\n",k);
        printf("ret[%d] = %d\n",j,k);
        ret[j] = (char*)ft_calloc(1, sizeof(char) * k + 1);
        j++;
        i++;
    }
}
char    **ft_split_for_mlx(char *string)
{
    char    **ret;

    if (!string)
        return (NULL);
    printf("How_many_split = %d\n",how_many_split(string));
    ret = (char**)ft_calloc(how_many_split(string) + 1,sizeof(char*));
    each_word_memory(string,ret);

    return (NULL);
}