/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:37:50 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/02 13:38:36 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"
#define SCALE 20

int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	return (fd);
}

char	*remove_space(char *string)
{
	int		i;
	int		k;
	char	*ret;

	k = 0;
	i = 0;
	while (string[i])
	{
		if (string[i] != ' ')
			k++;
		i++;
	}
	ret = malloc(sizeof(char) * k + 1);
	i = 0;
	k = 0;
	while (string[i])
	{
		if (string[i] != ' ')
		{
			ret[k] = string[i];
			k++;
		}
		i++;
	}
	ret[k] = '\0';
	return (free(string), ret);
}

void link_pxl(t_info* info, int x0, int y0, int x1, int y1)
{
			int dx = x1 - x0;
			int dy = y1 - y0;
			int incX = SGN(dx);
			int incY = SGN(dy);
			dx = ABS(dx);
			dy = ABS(dy);

			if (dy == 0)
			{
				// horizontal line
				for (int x = x0; x != x1 + incX; x += incX)
					mlx_put_pixel(info->img, x,y0, 0xFFFFFFFF);
			}
			else if (dx == 0)
			{
				// vertical line
				for (int y = y0; y != y1 + incY; y += incY)
					mlx_put_pixel(info->img, x0,y, 0xFFFFFFFF);
			}
			else if (dx >= dy)
			{
				// more horizontal than vertical
				int slope = 2 * dy;
				int error = -dx;
				int errorInc = -2 * dx;
				int y = y0;

				for (int x = x0; x != x1 + incX; x += incX)
				{
					mlx_put_pixel(info->img, x,y, 0xFFFFFFFF);
					error += slope;

					if (error >= 0)
					{
						y += incY;
						error += errorInc;
					}
				}
			}
			else
			{
				// more vertical than horizontal
				int slope = 2 * dx;
				int error = -dy;
				int errorInc = -2 * dy;
				int x = x0;

				for (int y = y0; y != y1 + incY; y += incY)
				{
					mlx_put_pixel(info->img, x,y, 0xFFFFFFFF);
					error += slope;

					if (error >= 0)
					{
						x += incX;
						error += errorInc;
					}
				}
			}
}

void isometric_transform_and_draw_line(t_info* info, int x0, int y0, int z0, int x1, int y1, int z1) {
    // Rotation autour de l'axe Z
    info->temp_x0 = x0 * cos(info->DEG_Z * M_PI / 180) - y0 * sin(info->DEG_Z * M_PI / 180);
    info->temp_y0 = x0 * sin(info->DEG_Z * M_PI / 180) + y0 * cos(info->DEG_Z * M_PI / 180);
    x0 = info->temp_x0;
    y0 = info->temp_y0;

    info->temp_x1 = x1 * cos(info->DEG_Z * M_PI / 180) - y1 * sin(info->DEG_Z * M_PI / 180);
    info->temp_y1 = x1 * sin(info->DEG_Z * M_PI / 180) + y1 * cos(info->DEG_Z * M_PI / 180);
    x1 = info->temp_x1;
    y1 = info->temp_y1;

    // Transform the start and end points to isometric projection
    int x0_iso = (x0 - z0) * cos(info->DEG_X * M_PI / 180) - (y0 - z0) * sin(info->DEG_X * M_PI / 180);
    int y0_iso = (x0 + z0) * sin(info->DEG_Y * M_PI / 180) + (y0 + z0) * cos(info->DEG_Y * M_PI / 180);
    int x1_iso = (x1 - z1) * cos(info->DEG_X * M_PI / 180) - (y1 - z1) * sin(info->DEG_X * M_PI / 180);
    int y1_iso = (x1 + z1) * sin(info->DEG_Y * M_PI / 180) + (y1 + z1) * cos(info->DEG_Y * M_PI / 180);

    // Now draw the line using the isometric coordinates
    if ((uint32_t)x0_iso + (info->img->width / 2) < info->img->width && 
        (uint32_t)y0_iso + (info->img->height / 2) < info->img->height && 
        (uint32_t)x1_iso + (info->img->width / 2) < info->img->width && 
        (uint32_t)y1_iso + (info->img->height / 2) < info->img->height) {
            link_pxl(info, x0_iso + (info->img->width / 2), y0_iso + (info->img->height / 2), 
                     x1_iso + (info->img->width / 2), y1_iso + (info->img->height / 2));
    }
}

void	parse_my_map(t_info *info, char *tab, char *tmp, int fd)
{
	while (tmp)
	{
		tmp = get_next_line(fd);
		tab = ft_strjoin(tab, tmp);
	}
	info->tab2d = ft_split_for_mlx(tab);
}

void start_put_pixel(t_info* info)
{
	int end;

	end = 0;
	while (info->tab2d[info->x0] && end != 1)
	{
		if (info->tab2d[info->x0 + 1])
		{
			isometric_transform_and_draw_line(info, info->x0 * SCALE, info->y0 * SCALE,ft_atoi(info->tab2d[info->x0][info->y0]), (info->x0 + 1) * SCALE, info->y0 * SCALE, ft_atoi(info->tab2d[info->x0 + 1][info->y0]));
			if (info->tab2d[info->x0][info->y0 + 1])
					isometric_transform_and_draw_line(info, info->x0 * SCALE, info->y0 * SCALE,ft_atoi(info->tab2d[info->x0][info->y0]), info->x0 * SCALE, (info->y0 + 1) * SCALE, ft_atoi(info->tab2d[info->x0][info->y0 + 1]));
			info->x0++;
		}
		else
		{
			if (info->tab2d[info->x0][info->y0 + 1])
				isometric_transform_and_draw_line(info, info->x0 * SCALE, info->y0 * SCALE,ft_atoi(info->tab2d[info->x0][info->y0]), info->x0 * SCALE, (info->y0 + 1) * SCALE, ft_atoi(info->tab2d[info->x0][info->y0 + 1]));
			info->x0 = 0;
			if (info->tab2d[info->x0][info->y0 + 1])
				info->y0++;
			else
				end = 1;
		}
		info->refresh = 0;
	}
}
void	put_pixel_on_map(t_info* info, char *path)
{
	int		fd;
	char *tab;
	char *tmp;
	
	tmp = ft_calloc(1, 1);
	if (!tmp)
		return ;
	tab = ft_calloc(1, 1);
	if (!tab)
		return ;
	fd = open_file(path);
	info->x0 = 0;
	info->y0 = 0;
	parse_my_map(info, tab, tmp, fd);
	start_put_pixel(info);
}


