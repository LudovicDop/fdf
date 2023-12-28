/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:37:50 by ldoppler          #+#    #+#             */
/*   Updated: 2023/12/28 22:49:07 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"
#define SCALE 2

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
void	put_pixel_on_map(t_info* info, char *path)
{
	int		fd;
	//t_increase x;
	char *tab;
	char *tmp;
	
	tmp = ft_calloc(1, 1);
	info->y0 = 30;
	info->x0 = 500;
	info->x1 = 1010;
	info->y1 = 30;
	tab = ft_calloc(1, 1);
	fd = open_file(path);
	while (tmp)
	{
		tmp = get_next_line(fd);
		tab = ft_strjoin(tab, tmp);
	}
	info->tab2d = ft_split_for_mlx(tab);

	info->x0 = 0;
	info->y0 = 0;
	int end;
	
	end = 0;
	while (info->tab2d[info->x0] && end != 1)
	{
		if (info->tab2d[info->x0 + 1])
		{
			printf("\n");
			printf("1Tab[%d][%d] = %s\n",info->x0, info->y0,info->tab2d[info->x0][info->y0]);
			printf("2Tab[%d][%d] = %s\n",info->x0 + 1, info->y0,info->tab2d[info->x0 + 1][info->y0]);
			link_pxl(info, info->x0 * SCALE, info->y0 * SCALE, (info->x0 + 1) * SCALE, info->y0 * SCALE);
			printf("\n");
			if (info->tab2d[info->x0][info->y0 + 1])
			{
				printf("3Tab[%d][%d] = %s\n",info->x0 , info->y0,info->tab2d[info->x0][info->y0]);
				printf("4Tab[%d][%d] = %s\n",info->x0, info->y0 + 1,info->tab2d[info->x0][info->y0 + 1]);
				link_pxl(info, info->x0, info->y0, info->x0 * SCALE, (info->y0 + 1) * SCALE);
			}
			info->x0++;
		}
		else
		{
			printf("\n");
			if (info->tab2d[info->x0][info->y0 + 1])
			{
				printf("6tab[%d][%d] = %s\n",info->x0, info->y0,info->tab2d[info->x0][info->y0]);
				printf("5tab[%d][%d] = %s\n",info->x0, info->y0 + 1,info->tab2d[info->x0][info->y0 + 1]);
				link_pxl(info, info->x0 * SCALE, info->y0 * SCALE, info->x0 * SCALE, (info->y0 + 1)* SCALE);
			}
			info->x0 = 0;
			if (info->tab2d[info->x0][info->y0 + 1])
			{
				info->y0++;
			}
			else
				end = 1;
		}
		info->refresh = 0;
	}
	//link_pxl(info,0,30,10,400);
}


