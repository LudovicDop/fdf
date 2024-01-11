/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:21:21 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/11 14:40:42 by ludovicdopp      ###   ########.fr       */
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

void	my_map_is_valid_bis(char *tmp, int *x_bis)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] != ' ' && tmp[i] != '\n')
		{
			(*x_bis)++;
			while (tmp[i] && tmp[i] != ' ')
				i++;
		}
		if (tmp[i])
			i++;
	}
}

void	my_map_is_valid(t_info *info, int *x)
{
	int		fd;
	int		x_bis;
	char	*tmp;

	x_bis = 0;
	fd = open_file(info->path);
	tmp = get_next_line(fd);
	if (!tmp)
		return (destroy_loop_hook(info));
	while (tmp)
	{
		my_map_is_valid_bis(tmp, &x_bis);
		free(tmp);
		tmp = get_next_line(fd);
		if (*x != x_bis)
		{
			ft_putstr_fd("Error\n", 2);
			return (exit(EXIT_FAILURE));
		}
		x_bis = 0;
	}
}

void	size2(t_info *info, int *x)
{
	int		fd;
	int		i;
	char	*tmp;

	fd = open_file(info->path);
	tmp = get_next_line(fd);
	additionnal_free(tmp, fd, info);
	i = 0;
	if (tmp)
	{
		while (tmp[i])
		{
			if (tmp[i] != ' ' && tmp[i] != '\n')
			{
				(*x)++;
				while (tmp[i] && tmp[i] != ' ' && tmp[i] != '\n')
					i++;
			}
			if (tmp[i])
				i++;
		}
		free(tmp);
		tmp = get_next_line(fd);
	}
	return (end(tmp, fd), my_map_is_valid(info, x), close(fd), free(tmp));
}

void	size(t_info *info, int *x, int *y)
{
	int		fd;
	char	*tmp;

	fd = open_file(info->path);
	if (fd < 0)
		return (free(info->path), free(info), exit(EXIT_FAILURE));
	tmp = get_next_line(fd);
	if (!tmp)
	{
		ft_putstr_fd("Error empty map\n", 2);
		close(fd);
		return (free(info->path), free(info), exit(EXIT_FAILURE));
	}
	while (tmp)
	{
		*y += 1;
		free(tmp);
		tmp = get_next_line(fd);
	}
	if (*y == 0)
		return (ft_putstr_fd("Error\n", 2), exit(EXIT_FAILURE));
	close(fd);
	free(tmp);
	size2(info, x);
}
