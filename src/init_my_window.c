/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_my_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:28:29 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/09 15:13:02 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"

int	init(t_info *info)
{
	t_info_map	*info_map;
	int			x;
	int			y;

	x = 0;
	y = -1;
	size(info, &x, &y);
	info->height = y;
	info->width = x;
	printf("x = %d && y = %d\n", x, y);
	// info->points = ft_calloc
	info_map = ft_calloc(x * y, sizeof(t_info_map));
	mlx_set_setting(MLX_MAXIMIZED, true);
	info->mlx = mlx_init(WIDTH, HEIGHT, "42FDF", true);
	if (!info->mlx)
		error();
	info->img = mlx_new_image(info->mlx, info->mlx->width, info->mlx->height);
	if (!info->img)
		error();
	if (mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
		error();
	parse(info, info_map, x * y);
	info->info_map = info_map;
	return (EXIT_SUCCESS);
}

void	destroy_loop_hook(t_info *info)
{
	// free_my_tab(info->tab2d);
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
