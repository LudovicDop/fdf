/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_for_mlx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:03:56 by ldoppler          #+#    #+#             */
/*   Updated: 2023/12/16 17:06:57 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>

int first_dimension(char *string)
{
    int i;
    int k;

    k = 0;
    i = 0;
    while (string[i])
    {
        if (string[i] == ' ')
        {
            printf("ok\n");
            k++;
        }
        if (string[i] == '\n')
        {
            printf("malloc first dimension = %d\n",k + 1);
            return (k++);
        }
        i++;
    }
}

int second_dimension(char *string,char ***ret)
{
    int i;
    int x;
    int y;

    y = 0;
    x = 0;
    i = 0;
    while (string[i])
    {
        if (string[i] == ' ' || string[i] == '\n')
        {
            printf("ret[%d] = x\n",x);
            ret[x] = (char**)ft_calloc(sizeof(char*), 1);
            x++;
        }
        if (string[i] == '\n')
            break;;
        i++;
    }
}

int each_word(char *string, char ***ret)
{
    int i;
    int x;
    int y;
    int z;

    x = 0;
    y = 0;
    z = 0;
    i = 0;
    while (string[i])
    {
        if (string[i] != ' ' && string[i] != '\n')
        {
            printf("ret[%d][%d][%d] = %c\n",x, y, z, string[i]);
        }
        if (string[i] == '\n')
        {
            y++;
        }
        if (string[i] == ' ')
            x++;
        i++;
    }
}

char    ***ft_split_for_mlx(char *string)
{
    char    ***ret;

    ret = (char***)ft_calloc(sizeof(char**),first_dimension(string));
    second_dimension(string, ret);
    each_word(string,ret);
}
