/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:37:50 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/10 18:12:07 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"

int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\n", 1);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	horizontal_pxl(t_iso *iso, unsigned int color, t_info *info)
{
	int	x;

	x = (int)iso->x0_iso;
	while (x != (int)iso->x1_iso + info->incX)
	{
		mlx_put_pixel(info->img, x, (int)iso->y0_iso, color);
		x += info->incX;
	}
}

void	vertical_pxl(t_iso *iso, unsigned int color, t_info *info)
{
	int	y;

	y = (int)iso->y0_iso;
	while (y != (int)iso->y1_iso + info->incY)
	{
		mlx_put_pixel(info->img, (int)iso->x0_iso, y, color);
		y += info->incY;
	}
}

void	put_pixel_on_map(t_info *info)
{
	start_put_pixel(info, info->info_map);
}
