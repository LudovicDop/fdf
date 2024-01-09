/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:37:50 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/09 15:13:31 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"
#define INDEX 0

int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\n", 1);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	horizontal_pxl(t_iso *iso, unsigned int color, t_info *info)
{
	int	x;

	x = (int)iso->x0_iso;
	while (x != (int)iso->x1_iso + info->incX)
	{
		mlx_put_pixel(info->img, x, (int)iso->y0_iso, color);
		x += info->incX;
	}
}

void	vertical_pxl(t_iso *iso, unsigned int color, t_info *info)
{
	int	y;

	y = (int)iso->y0_iso;
	while (y != (int)iso->y1_iso + info->incY)
	{
		mlx_put_pixel(info->img, (int)iso->x0_iso, y, color);
		y += info->incY;
	}
}

void	more_h_than_v(t_info *info, t_iso *iso, unsigned int color)
{
	info->slope = 2 * info->dy;
	info->error = -info->dx;
	info->error_inc = -2 * info->dx;
	info->y = (int)iso->y0_iso;
	info->x = (int)iso->x0_iso;
	while (info->x != (int)iso->x1_iso + info->incX)
	{
		mlx_put_pixel(info->img, info->x, info->y, color);
		info->error += info->slope;
		if (info->error >= 0)
		{
			info->y += info->incY;
			info->error += info->error_inc;
		}
		info->x += info->incX;
	}
}

void	more_v_than_h(t_info *info, t_iso *iso, unsigned int color)
{
	info->slope = 2 * info->dx;
	info->error = -info->dy;
	info->error_inc = -2 * info->dy;
	info->x = (int)iso->x0_iso;
	info->y = (int)iso->y0_iso;
	while (info->y != (int)iso->y1_iso + info->incY)
	{
		mlx_put_pixel(info->img, info->x, info->y, color);
		info->error += info->slope;
		if (info->error >= 0)
		{
			info->x += info->incX;
			info->error += info->error_inc;
		}
		info->y += info->incY;
	}
}

void	link_pxl(t_info *info, t_iso *iso, unsigned int color)
{
	info->dx = (int)iso->x1_iso - (int)iso->x0_iso;
	info->dy = (int)iso->y1_iso - (int)iso->y0_iso;
	info->incX = SGN(info->dx);
	info->incY = SGN(info->dy);
	info->dx = ABS(info->dx);
	info->dy = ABS(info->dy);
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

	radx = info->DEG_X * M_PI / 180;
	rady = info->DEG_Y * M_PI / 180;
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

void	parse2(char *buffer, t_info_map *info_map, int fd, int size)
{
	t_increase	x;
	char		**tmp;

	x.i = 0;
	x.x = 0;
	x.y = 0;
	while (buffer)
	{
		tmp = ft_split(buffer, ' ');
		if (!tmp)
			return (free(buffer));
		x.x = 0;
		info_map[x.i].x = -1;
		while (tmp[x.x] && x.i < size)
		{
			info_map[x.i].color = hex_to_uint(ft_strchr(tmp[x.x], ','));
			info_map[x.i].origin_z = ft_atoi(tmp[x.x]);
			info_map[x.i].origin_x = x.x;
			info_map[x.i].origin_y = x.y;
			x.x++;
			x.i++;
		}
		x.y++;
		buffer = get_next_line(fd);
	}
}
void	parse(t_info *info, t_info_map *info_map, int size)
{
	int		fd;
	char	*buffer;

	fd = open_file(info->path);
	buffer = get_next_line(fd);
	info_map[0].origin_x = 0;
	info_map[0].origin_y = 0;
	parse2(buffer, info_map, fd, size);
}

void	end(char *tmp, int fd)
{
	while (tmp)
		tmp = get_next_line(fd);
}
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
		tmp = get_next_line(fd);
		while (tmp && tmp[i])
		{
			if (tmp[i] != ' ')
			{
				*x += 1;
				while (tmp[i] && tmp[i] != ' ' && tmp[i] != '\n')
					i++;
			}
			i++;
		}
	}
	end(tmp, fd);
	return (close(fd), free(tmp));
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
		tmp = get_next_line(fd);
		*y += 1;
	}
	get_next_line(fd);
	close(fd);
	free(tmp);
	size2(info, x);
}

void	put_pixel_on_map(t_info *info)
{
	start_put_pixel(info, info->info_map);
}
