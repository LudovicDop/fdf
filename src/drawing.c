/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:37:50 by ldoppler          #+#    #+#             */
/*   Updated: 2023/12/27 23:50:48 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"
#define SCALE 42

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
	float slope = (float)(y1 - y0) / (float)(x1 - x0);
	for (int i = x0; i <= x1; ++i)
	{
		float y = slope * (i - x0) + y0;
		mlx_put_pixel(info->img, i,y, 0xFFFFFFFF);
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

	// while (info->tab2d[x.i])
	// {
	// 	x.j = 0;
	// 	while (info->tab2d[x.i][x.j])
	// 	{
	// 		printf("tab[%d][%d] = %s\n",x.i,x.j,info->tab2d[x.i][x.j]);
	// 		x.j++;
	// 	}
	// 	x.i++;
	// }

	// while (info->tab2d[x.i])
	// {
	// 	x.j = 0;
	// 	while (info->tab2d[x.i][x.j])
	// 	{
	// 		info->y0+=5;
	// 		info->y1+=5;
	// 		if ((uint32_t)info->x0 < info->img->width && (uint32_t)info->x1 < info->img->width && (uint32_t)info->y0 < info->img->height && (uint32_t)info->y1 < info->img->height)
	// 			link_pxl(info, info->x0, info->y0, info->x1, info->y1);
	// 		//printf("tab[%d][%d] = %s\n",x.i,x.j,info->tab2d[x.i][x.j]);
	// 		x.j++;
	// 	}
	// 	x.i++;
	// }
	//x.i = 0;
	//x.j = 0;
	// x.k = 0;
	// x.l = 0;
	// while (info->tab2d[x.i][x.j])
	// {
	// 	while (info->tab2d[x.i + 1])
	// 	{
	// 		x.j+=5;
	// 		printf("tab[%d][%d] = %s\n",x.i,x.j,info->tab2d[x.i][x.j]);
	// 		link_pxl(info, x.i, x.j, x.i + 10, x.j + 10);
	// 		x.i++;
	// 	} 
	// 	printf("\n");
	// 	x.i = 0;s
	// 	x.j++;
	// }
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
			printf("2Tab[%d][%d] = %s\n",info->x0, info->y0,info->tab2d[info->x0 + 1][info->y0]);
			printf("\n");
			printf("3Tab[%d][%d] = %s\n",info->x0, info->y0,info->tab2d[info->x0][info->y0]);
			printf("4Tab[%d][%d] = %s\n",info->x0, info->y0,info->tab2d[info->x0][info->y0 + 1]);
			info->x0++;
		}
		else
		{
			printf("\n");
			printf("6tab[%d][%d] = %s\n",info->x0, info->y0,info->tab2d[info->x0][info->y0]);
			printf("5tab[%d][%d] = %s\n",info->x0, info->y0,info->tab2d[info->x0][info->y0 + 1]);
			info->x0 = 0;
			if (info->tab2d[info->x0][info->y0 + 1])
			{
				info->y0++;
			}
			else
				end = 1;
		}
	}
}


