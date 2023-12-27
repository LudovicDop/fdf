/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_for_mlx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:03:56 by ldoppler          #+#    #+#             */
/*   Updated: 2023/12/27 14:55:32 by ldoppler         ###   ########.fr       */
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
    i = 0;
    while (i < first_dim)
    {
        ret[i] = (char**)ft_calloc(sizeof(char*), y + 1);
        i++;
    }
    ret[i] = NULL;
    return (1);
}

static void each_word(char *string, char ***ret)
{
    t_increase x;
    int each_word;

    x.i = 0;
    x.j = 0;
    x.k = 0;
    each_word = 0;
    while (string[x.i] && ret[x.k])
    {
        while (string[x.i] != ' ' && string[x.i] != '\n')
        {
            each_word++;
            x.i++;
        }
        if (string[x.i] == '\n')
        {
	        //printf("2) :ret[%d][%d]\n",x.k, x.j);
            ret[x.k][x.j++] = (char*)ft_calloc(sizeof(char),each_word + 1);
            each_word = 0;
            x.k = 0;
            x.i++;
        }
        if (string[x.i] == ' ')
        {
	        //printf("1) ret[%d][%d]\n",x.k, x.j);
            ret[x.k++][x.j] = (char*)ft_calloc(sizeof(char),each_word + 1);
            each_word = 0;
            while (string[x.i++] && string[x.i] == ' ');
        }
	if (string[x.i] == '\0')
	{
		//printf("daxa\n");
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
    x.k = 0;;
    each_word = 0;
    while (string[x.i])
    {
	    if (string[x.i + 1] == '\0' && string[x.i] == ' ')
		    break;
        while (string[x.i] != ' ' && string[x.i] != '\n' && string[x.i])
	    {
	        //printf("ret[%d][%d][%d] = %c\n",x.k, x.j, each_word, string[x.i]);
            ret[x.k][x.j][each_word++] = string[x.i++]; 
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

    first_dim = first_dimension(string);
    ret = (char***)ft_calloc(sizeof(char**),first_dim + 1);
    second_dimension(string, ret, first_dim);
    each_word(string,ret);
    implement(string,ret);
    return (ret);
}
