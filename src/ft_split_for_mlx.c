/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_for_mlx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:03:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/02 14:46:19 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/mlx.h"
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
            k++;
            return (k);
        }
        i++;
    }
    return (1);
}

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
    if (string[i - 1] != '\n')
        y++;
    printf("y = %d\n",y);
    i = 0;
    while (i < first_dim)
    {
        ret[i] = (char**)ft_calloc(sizeof(char*), y + 1);
        i++;
    }
    ret[i] = NULL;
    return (y);
}

static void each_word(char *string, char ***ret, int size, int second_dim)
{
    t_increase x;
    int each_word;

    x.i = 0;
    x.j = 0;
    x.k = 0;
    each_word = 0;
    printf("size = %d && second_dim = %d\n",size, second_dim);
    //&& (x.k < size && x.j < second_dim)
    while (string[x.i] && ret[x.k])
    {
        while (string[x.i] && string[x.i] != ' ' && string[x.i] != '\n')
        {
            each_word++;
            x.i++;
        }
        if (string[x.i] == '\n')
        {
            ret[x.k][x.j++] = (char*)ft_calloc(sizeof(char),each_word + 1);
            each_word = 0;
            x.k = 0;
            x.i++;
        }
        else if (string[x.i] == ' ')
        {
            ret[x.k++][x.j] = (char*)ft_calloc(sizeof(char),each_word + 1);
            each_word = 0;
            while (string[x.i++] && string[x.i] == ' ');
        }
	    if (string[x.i] == '\0')
	    {
		    if (string[x.i - 1] != '\n' && string[x.i - 1] != ' ')
                ret[x.k++][x.j] = (char*)ft_calloc(sizeof(char),each_word + 1);
		    break;
	    }
    }
}

static void implement(char *string, char ***ret)
{
    t_increase x;
    int each_word;

    x.i = 0;
    x.j = 0;
    x.k = 0;
    each_word = 0;
    while (string[x.i])
    {
	    if (string[x.i] && string[x.i + 1] == '\0' && string[x.i] == ' ')
		    break;
        while (string[x.i] && string[x.i] != ' ' && string[x.i] != '\n')
        {
            printf("ret[%d][%d][%d] ici %c\n", x.k, x.j, each_word, string[x.i]);
            ret[x.k][x.j][each_word] = string[x.i]; /*SEG FAULT*/
            //printf("ret[%d][%d][%d] = %c\n", x.k, x.j, each_word, string[x.i]);
            each_word++;
            x.i++;
        }
        if (string[x.i] == '\n')
        {
            each_word = 0;
            x.k = 0;
            x.j++;
            x.i++;
        }
        if (string[x.i] == ' ')
        {
            each_word = 0;
            x.k++;
            while (string[x.i++] && string[x.i] == ' ');
        }
    }
}

char    ***ft_split_for_mlx(char *string)
{
    char    ***ret;
    int     first_dim;
    int     second_dim;

    first_dim = first_dimension(string);
    ret = (char***)ft_calloc(sizeof(char**),first_dim + 1);
    second_dim =second_dimension(string, ret, first_dim);
    each_word(string,ret, first_dim, second_dim);
    implement(string,ret);
    printf("ko\n");
    return (ret);
}
