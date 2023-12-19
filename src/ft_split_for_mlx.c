/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_for_mlx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:03:56 by ldoppler          #+#    #+#             */
/*   Updated: 2023/12/19 15:53:30 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>

static int first_dimension(char *string)
{
    int i;
    int k;

    k = 0;
    i = 0;
    while (string[i])
    {
        if (string[i] == ' ')
        {
            k++;
            while(string[i] == ' ')
                i++;
        }
        if (string[i] == '\n')
        {
            printf("Malloc de x = %d\n",k);
            return (k);
        }
        i++;
    }
}
//ret[x] = (char**)ft_calloc(sizeof(char*), first_dimension(string) + 1);
static int second_dimension(char *string,char ***ret,int first_dim)
{
    int i;
    int y;

    y = 0;
    i = 0;
    while (string[i])
    {
        if (string[i] == '\n')
            y++;
        i++;
    }
    i = 0;
    while (i < first_dim)
    {
        printf("ret[%d] = calloc(%d + 1)\n",i,y);
        ret[i] = (char**)ft_calloc(sizeof(char*), y + 1);
        i++;
    }
    printf("y value = %d\n",y);
    return (y);
}
//ret[x][y] = (char*)ft_calloc(sizeof(char),each_word + 1);
static int each_word(char *string, char ***ret)
{
    int i;
    int x;
    int y;
    int each_word;

    each_word = 0;
    x = 0;
    y = 0;
    i = 0;
    while (string[i])
    {
        while (string[i] != ' ' && string[i] != '\n')
        {
            each_word++;
            i++;
        }
        if (string[i] == '\n')
        {
            printf("ret[%d][%d] = %d\n",x,y,each_word + 1);
            ret[x][y] = (char*)ft_calloc(sizeof(char),each_word + 1);
            each_word = 0;
            x = 0;
            y++;
            i++;
        }
        if (string[i] == ' ')
        {
            printf("|ret[%d][%d] = %d\n",x,y,each_word + 1);
            ret[x][y] = (char*)ft_calloc(sizeof(char),each_word + 1);
            each_word = 0;
            x++;
            while (string[i] && string[i] == ' ')
                i++;
        }
    }
}

static char*** implement(char *string, char ***ret)
{
    int i;
    int x;
    int y;
    int each_word;

    each_word = 0;
    x = 0;
    y = 0;
    i = 0;
    while (string[i])
    {
        while (string[i] != ' ' && string[i] != '\n')
        {
            ret[x][y][each_word] = string[i]; 
            each_word++;
            i++;
        }
        if (string[i] == '\n')
        {
            each_word = 0;
            x = 0;
            y++;
            i++;
        }
        if (string[i] == ' ')
        {
            each_word = 0;
            x++;
            while (string[i] && string[i] == ' ')
                i++;
        }
    }
}

char    ***ft_split_for_mlx(char *string)
{
    char    ***ret;
    int     first_dim;

    first_dim = first_dimension(string) + 1;
    ret = (char***)ft_calloc(sizeof(char**),first_dim);
    second_dimension(string, ret, first_dim);
    each_word(string,ret);
    implement(string,ret);
    return (ret);
}
