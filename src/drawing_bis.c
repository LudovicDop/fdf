/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:21:21 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/09 17:28:19 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx.h"

void	end(char *tmp, int fd)
{
	while (tmp)
	{
		tmp = get_next_line(fd);
		free(tmp);
	}
	free(tmp);
}

void	size2(t_info *info, int *x)
{
	int		fd;
	int		i;
	char	*tmp;

	fd = open_file(info->path);
	tmp = ft_calloc(1, 1);
	if (!tmp)
		return ;
	i = 0;
	if (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		while (tmp && tmp[i])
		{
			if (tmp[i] != ' ')
			{
				*x += 1;
				while (tmp[i++] && tmp[i] != ' ' && tmp[i] != '\n')
					;
			}
			i++;
		}
	}
	return (end(tmp, fd), close(fd), free(tmp));
}

void	size(t_info *info, int *x, int *y)
{
	int		fd;
	char	*tmp;

	fd = open_file(info->path);
	tmp = ft_calloc(1, 1);
	if (!tmp)
		return ;
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		*y += 1;
	}
	close(fd);
	free(tmp);
	size2(info, x);
}
