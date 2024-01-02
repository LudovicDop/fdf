/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_for_mlx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:03:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/02 21:17:37 by ldoppler         ###   ########.fr       */
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
    if (string[i] == ' ')
    {
        while (string[i] == ' ')
            i++;
    }
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
            printf("first dim = %d\n",k);
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
    //printf("y = %d\n",y);
    i = 0;
    while (i < first_dim)
    {
        printf("ret[%d] = %d\n",i, y + 1);
        ret[i] = (char**)ft_calloc(sizeof(char*), y + 1);
        i++;
    }
    ret[i] = NULL;
    //printf("second dim = %d\n",y);
    return (y);
}

// static void each_word(char *string, char ***ret, int size, int second_dim)
// {
//     t_increase x;
//     int each_word;

//     x.i = 0;
//     x.j = 0;
//     x.k = 0;
//     each_word = 0;
//     printf("size = %d && second_dim = %d\n",size, second_dim);
//     //&& (x.k < size && x.j < second_dim)
//     while (string[x.i] && ret[x.k] && (size_t)x.i < ft_strlen(string))
//     {
//         while (string[x.i] && string[x.i] != ' ' && string[x.i] != '\n' && (size_t)x.i < ft_strlen(string))
//         {
//             printf("each_word = %c\n",string[x.i]);
//             each_word++;
//             x.i++;
//         }
//         if (string[x.i] == '\n')
//         {
//             printf("ret[%d][%d] = %d\n",x.k, x.j, each_word);
//             ret[x.k][x.j++] = (char*)ft_calloc(sizeof(char),each_word + 1);
//             each_word = 0;
//             x.k = 0;
//             x.i++;
//         }
//         else if (string[x.i] == ' ' && each_word > 0 && (size_t)x.i < ft_strlen(string))
//         {
//             printf("!ret[%d][%d] = %d\n",x.k, x.j, each_word);
//             ret[x.k++][x.j] = (char*)ft_calloc(sizeof(char),each_word + 1);
//             each_word = 0;
//             while (string[x.i++] && string[x.i] == ' ');
//         }
//         else
//         {
//            x.i++;
//         }
// 	    if (string[x.i] == '\0')
// 	    {
// 		    if (string[x.i - 1] != '\n' && string[x.i - 1] != ' ' && each_word > 0)
//             {
//                 printf("#ret[%d][%d] = %d\n",x.k, x.j, each_word);
//                 ret[x.k++][x.j] = (char*)ft_calloc(sizeof(char),each_word + 1);

//             }
// 		    break;
// 	    }
//     }
// }
static void each_word(char *string, char ***ret)
{
    t_increase x;
    int each_word;
    int lock;

    lock = 0;
    each_word = 0;
    x.x = 0;
    x.y = 0;
    x.i = 0;
    printf("#DEBUT\n");
    while (string[x.i] && ret[x.x])
    {
        while (string[x.i] && string[x.i] != ' ' && string[x.i] != '\n')
        {
            lock = 1;
            each_word++;
            x.i++;
        }
        if (lock == 1)
        {
            printf("ret[%d][%d] = %d\n",x.x, x.y, each_word);
            ret[x.x][x.y] = ft_calloc(sizeof(char), each_word + 1);
            x.x++;
            lock = 0;
        }
        if (string[x.i] == '\n' && string[x.i])
        {
            each_word = 0;
            lock = 0;
            x.x = 0;
            x.y++;
            if (string[x.i + 1] == ' ')
            {
                x.i++;
                while (string[x.i] && string[x.i] == ' ')
                {
                    x.i++;
                }
            }
            else
                x.i++;
        }
        else if (string[x.i] == ' ' && string[x.i] )
        {
            lock = 0;
            each_word = 0;
            while (string[x.i] && string[x.i] == ' ')
            {
                x.i++;
            }
        }
    }
}
static void implement(char *string, char ***ret)
{
    t_increase x;
    int each_word;
    int lock;

    lock = 0;
    each_word = 0;
    x.x = 0;
    x.y = 0;
    x.i = 0;
    printf("#DEBUT\n");
    while (string[x.i] && ret[x.x])
    {
        while (string[x.i] && string[x.i] != ' ' && string[x.i] != '\n')
        {
            lock = 1;
            printf("ret[%d][%d][%d] = %c\n",x.x, x.y, each_word, string[x.i]);
            ret[x.x][x.y][each_word] = string[x.i];
            each_word++;
            x.i++;
        }
        if (lock == 1)
        {
            //printf("ret[%d][%d] = %d\n",x.x, x.y, each_word);
            //ret[x.x][x.y] = ft_calloc(sizeof(char), each_word + 1);
            x.x++;
            lock = 0;
        }
        if (string[x.i] == '\n' && string[x.i])
        {
            each_word = 0;
            lock = 0;
            x.x = 0;
            x.y++;
            if (string[x.i + 1] == ' ')
            {
                x.i++;
                while (string[x.i] && string[x.i] == ' ')
                {
                    x.i++;
                }
            }
            else
                x.i++;
        }
        else if (string[x.i] == ' ' && string[x.i] )
        {
            lock = 0;
            each_word = 0;
            while (string[x.i] && string[x.i] == ' ')
            {
                x.i++;
            }
        }
    }
}
// static void implement(char *string, char ***ret)
// {
//     t_increase x;
//     int each_word;

//     x.i = 0;
//     x.j = 0;
//     x.k = 0;
//     each_word = 0;
//     if (string[x.i] == ' ')
//     {
//         while (string[x.i] == ' ')
//             x.i++;
//     }
//     while (string[x.i])
//     {
// 	    if (string[x.i] && string[x.i + 1] == '\0' && string[x.i] == ' ')
// 		    break;
//         while (string[x.i] && string[x.i] != ' ' && string[x.i] != '\n')
//         {
//             //printf("ret[%d][%d][%d] ici %c\n", x.k, x.j, each_word, string[x.i]);
//             ret[x.k][x.j][each_word] = string[x.i]; /*SEG FAULT*/
//             printf("ret[%d][%d][%d] = %c\n", x.k, x.j, each_word, string[x.i]);
//             each_word++;
//             x.i++;
//         }
//         if (string[x.i] == '\n')
//         {
//             each_word = 0;
//             x.k = 0;
//             x.j++;
//             x.i++;
//         }
//         if (string[x.i] == ' ')
//         {
//             each_word = 0;
//             x.k++;
//             while (string[x.i++] && string[x.i] == ' ');
//         }
//     }
// }

char    ***ft_split_for_mlx(char *string)
{
    char    ***ret;
    int     first_dim;
    //int     second_dim;

    first_dim = first_dimension(string);
    ret = (char***)ft_calloc(sizeof(char**),first_dim + 1);
    second_dimension(string, ret, first_dim);
    each_word(string,ret);
    implement(string,ret);
    return (ret);
}
