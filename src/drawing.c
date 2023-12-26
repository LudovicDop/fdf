/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:37:50 by ldoppler          #+#    #+#             */
/*   Updated: 2023/12/26 19:32:09 by ldoppler         ###   ########.fr       */
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
	for(int i = x0; i <= x1; ++i)
	{
		float y = slope * (i - x0) + y0;
		mlx_put_pixel(info->img, i,y, 0xFFFFFFFF);
	}
}
void	put_pixel_on_map(t_info* info, char *path)
{
	int		fd;
	t_increase x;
	char *tab;
	char *tmp;

	info->y0 = 30;
	info->x0 = 500;
	info->x1 = 1010;
	info->y1 = 30;
	x.i = 0;
	x.j = 0;
	tab = ft_calloc(1, 1);
	fd = open_file(path);
	while (tmp)
	{
		tmp = get_next_line(fd);
		tab = ft_strjoin(tab, tmp);
	}
	info->tab2d = ft_split_for_mlx(tab);
	while (info->tab2d[x.i])
	{
		x.j = 0;
		while (info->tab2d[x.i][x.j])
		{
			link_pxl(info, info->x0, info->y0+=5, info->x1, info->y1+=5);
			printf("tab[%d][%d] = %s\n",x.i,x.j,info->tab2d[x.i][x.j]);
			x.j++;
		}
		x.i++;
	}
	
	// link_pxl(info, 0, 10, 100, 200);
}


