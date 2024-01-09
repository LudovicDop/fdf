/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bis2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:22:36 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/09 16:09:03 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx.h"

void	rotate_about_center(t_info_map *info_map, t_rot *rot, t_info *info)
{
	info->center_x = info->width / 2;
	info->center_y = info->height / 2;
	info->center_z = 0.0f;
	info_map->x = info_map->origin_x;
	info_map->y = info_map->origin_y;
	info_map->z = info_map->origin_z;
	info_map->x -= info->center_x;
	info_map->y -= info->center_y;
	info_map->z -= info->center_z;
	info->temp_y = info_map->y * cosf(info->rotation_angle_x) - info_map->z
		* sinf(info->rotation_angle_x);
	info->temp_z = info_map->y * sinf(info->rotation_angle_x) + info_map->z
		* cosf(info->rotation_angle_x);
	info_map->y = info->temp_y;
	info_map->z = info->temp_z;
	info->temp_x = info_map->x * cosf(info->rotation_angle_y) + info_map->z
		* sinf(info->rotation_angle_y);
	info->temp_z = -info_map->x * sinf(info->rotation_angle_y) + info_map->z
		* cosf(info->rotation_angle_y);
	rotate_about_center_bis(info, info_map, rot);
}

void	isometric_transform_and_draw_line(t_info *info, t_info_map *info_map,
		t_info_map *info_map2)
{
	t_rot	rot;
	t_rot	rot2;
	t_iso	iso;

	if (!info_map->color)
		info_map->color = 0xFFFFFFFF;
	rotate_about_center(info_map, &rot, info);
	rotate_about_center(info_map2, &rot2, info);
	isometric_transform(&rot, &iso.x0_iso, &iso.y0_iso, info);
	isometric_transform(&rot2, &iso.x1_iso, &iso.y1_iso, info);
	iso.x0_iso += info->img->width / 2;
	iso.y0_iso += info->img->height / 2;
	iso.x1_iso += info->img->width / 2;
	iso.y1_iso += info->img->height / 2;
	if (iso.x0_iso >= 0 && iso.x0_iso < info->img->width && iso.y0_iso >= 0
		&& iso.y0_iso < info->img->height && iso.x1_iso >= 0
		&& iso.x1_iso < info->img->width && iso.y1_iso >= 0
		&& iso.y1_iso < info->img->height)
	{
		link_pxl(info, &iso, info_map->color);
	}
}

void	start_put_pixel(t_info *info, t_info_map *info_map)
{
	int	i;
	int	node;

	node = info->width * info->height;
	i = 0;
	while (i < node)
	{
		if (info_map[i].origin_x < info->width && i < node - 1)
		{
			if (info_map[i].origin_x < info->width - 1)
				isometric_transform_and_draw_line(info, &info_map[i],
					&info_map[i + 1]);
			if (info_map[i].origin_y < info->height - 1)
				isometric_transform_and_draw_line(info, &info_map[i],
					&info_map[i + info->width]);
		}
		i++;
	}
}

int	ft_strlen_int(int number)
{
	int	i;

	i = 0;
	if (number < 0)
	{
		i++;
		number *= -1;
	}
	if (number == 0)
		return (1);
	while (number > 0)
	{
		number /= 10;
		i++;
	}
	return (i);
}

unsigned int	hex_to_uint(const char *hex)
{
	unsigned int	result;

	result = 0;
	if (!hex)
		return (0);
	while (*hex)
	{
		result *= 16;
		if (*hex >= '0' && *hex <= '9')
		{
			result += *hex - '0';
		}
		else if (*hex >= 'a' && *hex <= 'f')
		{
			result += *hex - 'a' + 10;
		}
		else if (*hex >= 'A' && *hex <= 'F')
		{
			result += *hex - 'A' + 10;
		}
		++hex;
	}
	result = (result << 8) | 0xFF;
	return (result);
}
