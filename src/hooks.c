/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:19:08 by ldoppler          #+#    #+#             */
/*   Updated: 2023/12/12 18:45:15 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"

void	ft_hook(void *param)
{
	t_info	*info;

	info = param;
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	if (info->refresh == 1)
	{
		put_pixel_on_map(info, info->path);
	}
}

void	ft_hook_resize(int width, int height, void *param)
{
	t_info	*info;

	info = param;
	resize_img(info->img, width, height);
	info->refresh = 1;
}

void	resize_img(mlx_image_t *img, unsigned int width, unsigned int height)
{
	int	x;
	int	y;

	mlx_resize_image(img, width, height);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}
