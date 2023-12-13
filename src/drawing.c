/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:37:50 by ldoppler          #+#    #+#             */
/*   Updated: 2023/12/13 14:14:59 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"

int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	return (fd);
}

void	put_pixel_on_map(t_info* info, char *path)
{
	int		fd;
	char *tmp;
	char **buffer;
	coord_t *coord;
	
	coord = ft_calloc(1, sizeof(coord_t));
	coord->x = 0;
	coord->y = 0;
	fd = open_file(path);
	tmp = get_next_line(fd);
	buffer = ft_split(tmp,' ');
	while (tmp)
	{
		while (*buffer)
		{
			mlx_put_pixel(info->img, coord->x + ((info->img->width / 2)), coord->y + ((info->img->height / 2)), 0xFFFFFFFF);
			coord->x+= 28;
			printf("%s\n",*buffer);
			*buffer++;
		}
		if (*buffer == NULL)
		{
			printf("ok\n");
			tmp = get_next_line(fd);
			buffer = ft_split(tmp,' ');
			coord->x = 0;
			coord->y+= 28;
		}
	}
	mlx_image_to_window(info->mlx, info->img, 0, 0);
	info->refresh = 0;
}