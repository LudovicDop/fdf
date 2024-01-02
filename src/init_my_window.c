/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_my_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:28:29 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/02 22:02:35 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"

int	init(t_info *info)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	info->mlx = mlx_init(WIDTH, HEIGHT, "42FDF", true);
	if (!info->mlx)
		error();
	info->img = mlx_new_image(info->mlx, info->mlx->width, info->mlx->height);
	if (!info->img)
		error();
	if (mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
		error();
	return (EXIT_SUCCESS);
}

void	destroy_loop_hook(t_info *info)
{
	//free_my_tab(info->tab2d);
	mlx_delete_image(info->mlx, info->img);
	mlx_terminate(info->mlx);
	free(info->path);
	free(info);
}

void	init_loop_hook(t_info *info)
{
	mlx_loop_hook(info->mlx, ft_hook, info);
	mlx_resize_hook(info->mlx, ft_hook_resize, info);
}
