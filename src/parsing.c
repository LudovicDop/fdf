/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:24:12 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/11 13:52:19 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx.h"

void	parse3(t_info_map *info_map, t_increase *x, char **tmp)
{
	info_map[x->i].color = hex_to_uint(ft_strchr(tmp[x->x], ','));
	info_map[x->i].origin_z = ft_atoi(tmp[x->x]);
	info_map[x->i].origin_x = x->x;
	info_map[x->i].origin_y = x->y;
	x->x++;
	x->i++;
}

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
			parse3(info_map, &x, tmp);
		}
		x.y++;
		free(buffer);
		buffer = get_next_line(fd);
		free_char_array(tmp);
	}
	free(buffer);
}

void	parse(t_info *info, t_info_map *info_map, int size)
{
	int		fd;
	char	*buffer;

	fd = open_file(info->path);
	if (fd < 0)
		return (destroy_loop_hook(info));
	buffer = get_next_line(fd);
	info_map[0].origin_x = 0;
	info_map[0].origin_y = 0;
	parse2(buffer, info_map, fd, size);
}
