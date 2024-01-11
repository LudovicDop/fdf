/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:08:05 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/11 14:22:52 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx.h"

void	free_char_array(char **array)
{
	int	i;

	if (array == NULL)
	{
		return ;
	}
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	abs(int x)
{
	if (x >= 0)
		return (x);
	else
		return (-x);
}

int	sgn(int x)
{
	if (x < 0)
		return (-1);
	else if (x > 0)
		return (1);
	else
		return (0);
}

void	additionnal_free(char *tmp, int fd, t_info *info)
{
	if (!tmp || fd < 0)
		return (close(fd), destroy_loop_hook(info));
}
