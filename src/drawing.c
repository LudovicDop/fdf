/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:37:50 by ldoppler          #+#    #+#             */
/*   Updated: 2023/12/19 16:14:41 by ldoppler         ###   ########.fr       */
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
void	put_pixel_on_map(t_info* info, char *path)
{
	int		fd;
	char *tab;
	char *tmp;
	//t_increase increase;

	//increase.i = 0;
	//increase.j = 0;
	//increase.k = 0;
	tab = ft_calloc(1, 1);
	fd = open_file(path);
	while (tmp)
	{
		tmp = get_next_line(fd);
		tab = ft_strjoin(tab, tmp);
	}
	//info->tab2d = ft_split_for_mlx(tab);
	info->tab2d = ft_split_for_mlx(tab);
	printf("ret[%d][%d] = %s\n",0,2,info->tab2d[0][2]);
	//printf("%s\n",info->tab2d[5][4]);
	//printf("tab[%d][%d] = %p\n",increase.i, increase.j,info->tab2d[7]);
	// while (info->tab2d[increase.i] != NULL)
	// {
	// 	increase.j = 0;
	// 	while (info->tab2d[increase.i][increase.j] != NULL)
	// 	{
	// 			printf("tab[%d][%d] = %s\n",increase.i, increase.j,info->tab2d[increase.i][increase.j]);
	// 			increase.j++;
	// 	}
	// 	increase.i++;
	// }
	mlx_image_to_window(info->mlx, info->img, 250, 250);
	info->refresh = 0;
}
