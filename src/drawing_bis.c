/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:21:21 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/09 16:07:51 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx.h"

void	parse2(char *buffer, t_info_map *info_map, int fd, int size)
{
	t_increase	x;
	char		**tmp;

	x.i = 0;
	x.x = 0;
	x.y = 0;
	while (buffer)
	{
		tmp = ft_split(buffer, ' ');
		if (!tmp)
			return (free(buffer));
		x.x = 0;
		info_map[x.i].x = -1;
		while (tmp[x.x] && x.i < size)
		{
			info_map[x.i].color = hex_to_uint(ft_strchr(tmp[x.x], ','));
			info_map[x.i].origin_z = ft_atoi(tmp[x.x]);
			info_map[x.i].origin_x = x.x;
			info_map[x.i].origin_y = x.y;
			x.x++;
			x.i++;
		}
		x.y++;
		buffer = get_next_line(fd);
	}
}

void	parse(t_info *info, t_info_map *info_map, int size)
{
	int		fd;
	char	*buffer;

	fd = open_file(info->path);
	buffer = get_next_line(fd);
	info_map[0].origin_x = 0;
	info_map[0].origin_y = 0;
	parse2(buffer, info_map, fd, size);
}

void	end(char *tmp, int fd)
{
	while (tmp)
		tmp = get_next_line(fd);
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
		tmp = get_next_line(fd);
		while (tmp && tmp[i])
		{
			if (tmp[i] != ' ')
			{
				*x += 1;
				while (tmp[i] && tmp[i] != ' ' && tmp[i] != '\n')
					i++;
			}
			i++;
		}
	}
	end(tmp, fd);
	return (close(fd), free(tmp));
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
		tmp = get_next_line(fd);
		*y += 1;
	}
	get_next_line(fd);
	close(fd);
	free(tmp);
	size2(info, x);
}
