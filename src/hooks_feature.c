/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_feature.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:54:23 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/09 16:09:37 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx.h"

void	ft_hooks_s(t_info *info)
{
	mlx_delete_image(info->mlx, info->img);
	info->img = mlx_new_image(info->mlx, info->mlx->width, info->mlx->height);
	if (!info->img)
		error();
	if (mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
		error();
	resize_img(info->img, info->img->width, info->img->height);
	info->rotation_angle_x -= 0.1;
	put_pixel_on_map(info);
}

void	ft_hooks_d(t_info *info)
{
	mlx_delete_image(info->mlx, info->img);
	info->img = mlx_new_image(info->mlx, info->mlx->width, info->mlx->height);
	if (!info->img)
		error();
	if (mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
		error();
	resize_img(info->img, info->img->width, info->img->height);
	info->rotation_angle_y += 0.1;
	put_pixel_on_map(info);
}

void	ft_hooks_x(t_info *info)
{
	mlx_delete_image(info->mlx, info->img);
	info->img = mlx_new_image(info->mlx, info->mlx->width, info->mlx->height);
	if (!info->img)
		error();
	if (mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
		error();
	resize_img(info->img, info->img->width, info->img->height);
	info->scale += 0.1f;
	put_pixel_on_map(info);
}

void	ft_hooks_a(t_info *info)
{
	mlx_delete_image(info->mlx, info->img);
	info->img = mlx_new_image(info->mlx, info->mlx->width, info->mlx->height);
	if (!info->img)
		error();
	if (mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
		error();
	resize_img(info->img, info->img->width, info->img->height);
	info->rotation_angle_y -= 0.1;
	put_pixel_on_map(info);
}

void	ft_hooks_c(t_info *info)
{
	mlx_delete_image(info->mlx, info->img);
	info->img = mlx_new_image(info->mlx, info->mlx->width, info->mlx->height);
	if (!info->img)
		error();
	if (mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
		error();
	resize_img(info->img, info->img->width, info->img->height);
	info->scale -= 0.1f;
	put_pixel_on_map(info);
}
