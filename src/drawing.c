/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:37:50 by ldoppler          #+#    #+#             */
/*   Updated: 2023/12/16 15:52:01 by ldoppler         ###   ########.fr       */
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
	char ***tab2d;
	char *tab;
	char *tmp;
	char test;

	tab = ft_calloc(1, 1);
	fd = open_file(path);
	while (tmp)
	{
		tmp = get_next_line(fd);
		tab = ft_strjoin(tab, tmp);
	}
	ft_split_for_mlx(tab);
	printf("OK\n");
	//tab = remove_space(tab);
	printf("END\n");
	//tab2d = ft_split(tab,'\n');
	//printf("%c\n",tab2d[2][2]);
	mlx_image_to_window(info->mlx, info->img, 250, 250);
	info->refresh = 0;
}
