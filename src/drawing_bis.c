/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:21:21 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/09 18:22:12 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx.h"

void	end(char *tmp, int fd)
{
	while (tmp)
	{
		tmp = get_next_line(fd);
		free(tmp);
	}
	free(tmp);
}

// void my_map_is_valid(t_info* info, int *x)
// {
// 	int		fd;
// 	int		i;
// 	int		x_bis;
// 	char	*tmp;

// 	x_bis = -1;
// 	fd = open_file(info->path);
// 	tmp = get_next_line(fd);
// 	if (!tmp)
// 		return ;
// 	while (tmp)
// 	{
// 		i = 0;
// 		while (tmp && tmp[i])
// 		{
// 			if (tmp[i] != ' ')
// 			{
// 				while (tmp[i] != ' ' && tmp[i + 1])
// 				{
// 					i++;
// 				}
// 				x_bis++;
// 			}
// 			i++;
// 		}
// 		//printf("%s\n",tmp);
// 		printf("x = %d && %d\n",x_bis,*x);
// 		if (*x != x_bis)
// 		{
// 			ft_putstr_fd("Error rip\n",1);
// 			exit(EXIT_FAILURE);
// 		}
// 		x_bis = 0;
// 		free(tmp);
// 		tmp = get_next_line(fd);
// 	}

// }

void	size2(t_info *info, int *x)
{
	int		fd;
	int		i;
	char	*tmp;

	fd = open_file(info->path);
	tmp = ft_calloc(1, 1);
	if (!tmp)
		return ;
	i = 0;
	if (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		while (tmp && tmp[i])
		{
			if (tmp[i] != ' ')
			{
				*x += 1;
				while (tmp[i++] && tmp[i] != ' ' && tmp[i] != '\n')
					;
			}
			i++;
		}
	}
	//return (my_map_is_valid(info,x),end(tmp, fd), close(fd), free(tmp));
	return (end(tmp, fd), close(fd), free(tmp));
}

void	size(t_info *info, int *x, int *y)
{
	int		fd;
	char	*tmp;

	fd = open_file(info->path);
	tmp = ft_calloc(1, 1);
	if (!tmp)
		return ;
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		*y += 1;
	}
	close(fd);
	free(tmp);
	size2(info, x);
}
