/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:37:50 by ldoppler          #+#    #+#             */
/*   Updated: 2023/12/12 16:40:50 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"


char	**get_line(int fd)
{
	char	*buffer;
	char	*read_line;
	char	**tab;

	read_line = ft_calloc(1, 1);
	while (buffer)
	{
		buffer = ft_strdup(get_next_line(fd));
		read_line = ft_strjoin(read_line, buffer);
	}
	tab = ft_split(read_line, ' ');
	return (tab);
}

int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	return (fd);
}

void	put_pixel_on_map(mlx_image_t *img, mlx_t *mlx, char *path)
{
	int		fd;
	char	**tab;
	coord_t	*coord;
	int		i;

	i = 0;
	coord->x = 0;
	coord->y = 0;
	coord->z = 0;
	fd = open_file(path);
	tab = get_line(fd);
	while (tab[i])
	{
		mlx_put_pixel(img, coord->x + (img->width / 2), coord->y + (img->height
				/ 2), 0xFF000000);
		if (tab[i][1] != '\n')
		{
			coord->x++;
		}
		else
		{
			coord->x = 0;
			coord->y++;
		}
		i++;
	}
	while (*tab)
	{
		printf("%s", *tab);
		*tab++;
	}
}