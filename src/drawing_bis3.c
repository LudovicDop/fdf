/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bis3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:23:09 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/10 18:28:36 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx.h"

void	more_h_than_v(t_info *info, t_iso *iso, unsigned int color)
{
	info->slope = 2 * info->dy;
	info->error = -info->dx;
	info->error_inc = -2 * info->dx;
	info->y = (int)iso->y0_iso;
	info->x = (int)iso->x0_iso;
	while (info->x != (int)iso->x1_iso + info->inc_x)
	{
		mlx_put_pixel(info->img, info->x, info->y, color);
		info->error += info->slope;
		if (info->error >= 0)
		{
			info->y += info->inc_y;
			info->error += info->error_inc;
		}
		info->x += info->inc_x;
	}
}

void	more_v_than_h(t_info *info, t_iso *iso, unsigned int color)
{
	info->slope = 2 * info->dx;
	info->error = -info->dy;
	info->error_inc = -2 * info->dy;
	info->x = (int)iso->x0_iso;
	info->y = (int)iso->y0_iso;
	while (info->y != (int)iso->y1_iso + info->inc_y)
	{
		mlx_put_pixel(info->img, info->x, info->y, color);
		info->error += info->slope;
		if (info->error >= 0)
		{
			info->x += info->inc_x;
			info->error += info->error_inc;
		}
		info->y += info->inc_y;
	}
}

void	link_pxl(t_info *info, t_iso *iso, unsigned int color)
{
	info->dx = (int)iso->x1_iso - (int)iso->x0_iso;
	info->dy = (int)iso->y1_iso - (int)iso->y0_iso;
	info->inc_x = sgn(info->dx);
	info->inc_y = sgn(info->dy);
	info->dx = abs(info->dx);
	info->dy = abs(info->dy);
	if (info->dy == 0)
		horizontal_pxl(iso, color, info);
	else if (info->dx == 0)
		vertical_pxl(iso, color, info);
	else if (info->dx >= info->dy)
		more_h_than_v(info, iso, color);
	else
		more_v_than_h(info, iso, color);
}

void	isometric_transform(t_rot *rot, float *x_iso, float *y_iso,
		t_info *info)
{
	float	radx;
	float	rady;

	radx = info->deg_x * M_PI / 180;
	rady = info->deg_y * M_PI / 180;
	*x_iso = (rot->x0_rot - rot->z0_rot) * cosf(radx) * info->scale;
	*y_iso = (rot->y0_rot + (rot->x0_rot + rot->z0_rot) * sinf(rady))
		* info->scale;
}

void	rotate_about_center_bis(t_info *info, t_info_map *info_map, t_rot *rot)
{
	info_map->x = info->temp_x;
	info_map->z = info->temp_z;
	info->temp_x = info_map->x * cosf(info->rotation_angle_z) - info_map->y
		* sinf(info->rotation_angle_z);
	info->temp_y = info_map->x * sinf(info->rotation_angle_z) + info_map->y
		* cosf(info->rotation_angle_z);
	info_map->x = info->temp_x * info->scale;
	info_map->y = info->temp_y * info->scale;
	info_map->z = info->temp_z;
	rot->x0_rot = info_map->x + info->center_x;
	rot->y0_rot = info_map->y + info->center_y;
	rot->z0_rot = info_map->z + info->center_z;
}
