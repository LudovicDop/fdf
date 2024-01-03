/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:19:08 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/03 17:49:43 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"

void	ft_hook(void *param)
{
	t_info	*info;

	info = param;
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(info->mlx);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_W))
	{
		mlx_delete_image(info->mlx, info->img);
		info->img = mlx_new_image(info->mlx, info->mlx->width, info->mlx->height);
		if (!info->img)
			error();
		if (mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
			error();
		resize_img(info->img, info->img->width, info->img->height);
		info->rotation_angle_x+=0.1;
		put_pixel_on_map(info, info->path);
	}
	else if (mlx_is_key_down(info->mlx, MLX_KEY_S))
	{
		mlx_delete_image(info->mlx, info->img);
		info->img = mlx_new_image(info->mlx, info->mlx->width, info->mlx->height);
		if (!info->img)
			error();
		if (mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
			error();
		resize_img(info->img, info->img->width, info->img->height);
		put_pixel_on_map(info, info->path);
		info->rotation_angle_x-=0.1;
	}
	else if (mlx_is_key_down(info->mlx, MLX_KEY_D))
	{
		mlx_delete_image(info->mlx, info->img);
		info->img = mlx_new_image(info->mlx, info->mlx->width, info->mlx->height);
		if (!info->img)
			error();
		if (mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
			error();
		resize_img(info->img, info->img->width, info->img->height);
		put_pixel_on_map(info, info->path);
		info->rotation_angle_y+=0.1;
	}
	else if (mlx_is_key_down(info->mlx, MLX_KEY_A))
	{
		mlx_delete_image(info->mlx, info->img);
		info->img = mlx_new_image(info->mlx, info->mlx->width, info->mlx->height);
		if (!info->img)
			error();
		if (mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
			error();
		resize_img(info->img, info->img->width, info->img->height);
		put_pixel_on_map(info, info->path);
		info->rotation_angle_y-=0.1;
	}
	else if (mlx_is_key_down(info->mlx, MLX_KEY_X))
	{
		mlx_delete_image(info->mlx, info->img);
		info->img = mlx_new_image(info->mlx, info->mlx->width, info->mlx->height);
		if (!info->img)
			error();
		if (mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
			error();
		resize_img(info->img, info->img->width, info->img->height);
		put_pixel_on_map(info, info->path);
		info->scale++;
	}
	else if (mlx_is_key_down(info->mlx, MLX_KEY_C))
	{
		mlx_delete_image(info->mlx, info->img);
		info->img = mlx_new_image(info->mlx, info->mlx->width, info->mlx->height);
		if (!info->img)
			error();
		if (mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
			error();
		resize_img(info->img, info->img->width, info->img->height);
		put_pixel_on_map(info, info->path);
		info->scale--;
	}
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
	while ((uint32_t)y < img->height)
	{
		x = 0;
		while ((uint32_t)x < img->width)
		{
			mlx_put_pixel(img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}
