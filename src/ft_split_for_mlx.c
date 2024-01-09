/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_for_mlx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:03:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/09 15:14:23 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx.h"
#include "../libft/libft.h"
#include <stdio.h>

static int	first_dimension(char *string)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	if (string[i] == ' ')
		while (string[i] == ' ')
			i++;
	while (string[i])
	{
		if (string[i] == ' ')
		{
			k++;
			while (string[i] == ' ')
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

static int	second_dimension(char *string, char ***ret, int first_dim)
{
	int	i;
	int	y;

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
	i = 0;
	while (i < first_dim)
	{
		ret[i] = (char **)ft_calloc(sizeof(char *), y + 1);
		i++;
	}
	ret[i] = NULL;
	return (y);
}

static void	each_word(char *string, char ***ret)
{
	t_increase	x;
	int			each_word;
	int			lock;

	lock = 0;
	each_word = 0;
	x.x = 0;
	x.y = 0;
	x.i = 0;
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
		else if (string[x.i] == ' ' && string[x.i])
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
static void	implement(char *string, char ***ret)
{
	t_increase	x;
	int			each_word;
	int			lock;

	lock = 0;
	each_word = 0;
	x.x = 0;
	x.y = 0;
	x.i = 0;
	while (string[x.i] && ret[x.x])
	{
		while (string[x.i] && string[x.i] != ' ' && string[x.i] != '\n')
		{
			lock = 1;
			ret[x.x][x.y][each_word] = string[x.i];
			each_word++;
			x.i++;
		}
		if (lock == 1)
		{
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
		else if (string[x.i] == ' ' && string[x.i])
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

char	***ft_split_for_mlx(char *string)
{
	char	***ret;
	int		first_dim;

	first_dim = first_dimension(string);
	ret = (char ***)ft_calloc(sizeof(char **), first_dim + 1);
	second_dimension(string, ret, first_dim);
	each_word(string, ret);
	implement(string, ret);
	return (ret);
}
