/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:37:50 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/08 17:19:48 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"
#define INDEX 0
int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	return (fd);
}

void link_pxl(t_info* info, int x0, int y0, int x1, int y1, unsigned int color)
{
			int dx = x1 - x0;
			int dy = y1 - y0;
			int incX = SGN(dx);
			int incY = SGN(dy);
			dx = ABS(dx);
			dy = ABS(dy);
	
			if (dy == 0)
			{
				// horizontal line
				for (int x = x0; x != x1 + incX; x += incX)
					mlx_put_pixel(info->img, x,y0, color);
			}
			else if (dx == 0)
			{
				// vertical line
				for (int y = y0; y != y1 + incY; y += incY)
					mlx_put_pixel(info->img, x0,y, color);
			}
			else if (dx >= dy)
			{
				// more horizontal than vertical
				int slope = 2 * dy;
				int error = -dx;
				int errorInc = -2 * dx;
				int y = y0;

				for (int x = x0; x != x1 + incX; x += incX)
				{
					mlx_put_pixel(info->img, x,y, color);
					error += slope;

					if (error >= 0)
					{
						y += incY;
						error += errorInc;
					}
				}
			}
			else
			{
				// more vertical than horizontal
				int slope = 2 * dx;
				int error = -dy;
				int errorInc = -2 * dy;
				int x = x0;

				for (int y = y0; y != y1 + incY; y += incY)
				{
					mlx_put_pixel(info->img, x,y, color);
					error += slope;

					if (error >= 0)
					{
						x += incX;
						error += errorInc;
					}
				}
			}
}


//0xFFFFFFFF
void isometric_transform(float x, float y, float z, float *x_iso, float *y_iso, t_info* info) {
    float radX = info->DEG_X * M_PI / 180;
    float radY = info->DEG_Y * M_PI / 180;

    *x_iso = (x - z) * cosf(radX) * info->scale;
    *y_iso = (y + (x + z) * sinf(radY)) * info->scale;
}

void rotate_about_center(float x, float y, float z, float *x_rot, float *y_rot, float *z_rot, t_info *info) {
    float center_x = info->width / 2; // Define center x
    float center_y = info->height / 2; // Define center y
    float center_z = 0.0f; // Define center z

    x -= center_x;
    y -= center_y;
    z -= center_z;
    float temp_y = y * cosf(info->rotation_angle_x) - z * sinf(info->rotation_angle_x);
    float temp_z = y * sinf(info->rotation_angle_x) + z * cosf(info->rotation_angle_x);
    y = temp_y;
    z = temp_z;
    float temp_x = x * cosf(info->rotation_angle_y) + z * sinf(info->rotation_angle_y);
    temp_z = -x * sinf(info->rotation_angle_y) + z * cosf(info->rotation_angle_y);
    x = temp_x;
    z = temp_z;
    temp_x = x * cosf(info->rotation_angle_z) - y * sinf(info->rotation_angle_z);
    temp_y = x * sinf(info->rotation_angle_z) + y * cosf(info->rotation_angle_z);
    x = temp_x * info->scale;
    y = temp_y * info->scale;
    z = temp_z;
    *x_rot = x + center_x;
    *y_rot = y + center_y;
    *z_rot = z + center_z;
}

//void isometric_transform_and_draw_line(t_info* info, float x0, float y0, float z0, float x1, float y1, float z1, unsigned int color) {
void isometric_transform_and_draw_line(t_info* info, t_info_map* info_map, t_info_map* info_map2) {
    t_rot	rot;
	t_iso	iso;

	if (!info_map->color)
		info_map->color = 0xFFFFFFFF;
    // Apply rotation around the center
    rotate_about_center(info_map->x, info_map->y, info_map->z, &rot.x0_rot, &rot.y0_rot, &rot.z0_rot, info);
    rotate_about_center(info_map2->x, info_map2->y, info_map2->z, &rot.x1_rot, &rot.y1_rot, &rot.z1_rot, info);

    // Apply isometric transformation to start and end points
    isometric_transform(rot.x0_rot, rot.y0_rot, rot.z0_rot, &iso.x0_iso, &iso.y0_iso, info);
    isometric_transform(rot.x1_rot, rot.y1_rot, rot.z1_rot, &iso.x1_iso, &iso.y1_iso, info);

    // Adjust for the center of the image
    iso.x0_iso += info->img->width / 2;
    iso.y0_iso += info->img->height / 2;
    iso.x1_iso += info->img->width / 2;
    iso.y1_iso += info->img->height / 2;

    // Check if the coordinates are within the bounds of the image
    if (iso.x0_iso >= 0 && iso.x0_iso < info->img->width && iso.y0_iso >= 0 && iso.y0_iso < info->img->height &&
        iso.x1_iso >= 0 && iso.x1_iso < info->img->width && iso.y1_iso >= 0 && iso.y1_iso < info->img->height) {
        // Draw the line using isometric coordinates
        link_pxl(info, iso.x0_iso, iso.y0_iso, iso.x1_iso, iso.y1_iso, info_map->color);
    }
}

void start_put_pixel(t_info* info, t_info_map* info_map)
{
	int i;
	int node;

	node = info->width * info->height;
	i = 0;
	while (i < node)
	{ 
		if (info_map[i].x < info->width && i < node - 1) 
		{
			if (info_map[i].x < info->width - 1)
								isometric_transform_and_draw_line(info, &info_map[i], &info_map[i + 1]);
			if (info_map[i].y < info->height - 1)
								isometric_transform_and_draw_line(info, &info_map[i], &info_map[i + info->width]);
		}
		i++;
	}
}

int	ft_strlen_int(int number)
{
	int i;

	i = 0;
	if (number < 0)
	{
		i++;
		number*=-1;
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

unsigned int hex_to_uint(const char *hex) {
    unsigned int result = 0;

	if (!hex)
		return (0);
    while (*hex) {
        result *= 16;
        if (*hex >= '0' && *hex <= '9') {
            result += *hex - '0';
        } else if (*hex >= 'a' && *hex <= 'f') {
            result += *hex - 'a' + 10;
        } else if (*hex >= 'A' && *hex <= 'F') {
            result += *hex - 'A' + 10;
        }
        ++hex;
    }

    // Ajout de FF à la fin
    result = (result << 8) | 0xFF;
    
    return result;
}

void	parse2(char *buffer, t_info_map* info_map, int fd, int size)
{
	t_increase x;
	char	**tmp;

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
			info_map[x.i].z = ft_atoi(tmp[x.x]);
			info_map[x.i].x = x.x;
			info_map[x.i].y = x.y;
			x.x++;
			x.i++;
		}
		x.y++;
		buffer = get_next_line(fd);
	}
}
void	parse(t_info* info, t_info_map *info_map, int size)
{
	int	fd;
	char *buffer;

	fd = open_file(info->path);
	buffer = get_next_line(fd);
	info_map[0].x = 0;
	info_map[0].y = 0;
	parse2(buffer, info_map, fd, size);
}

void	end(char *tmp, int fd)
{
	while (tmp)
		tmp = get_next_line(fd);
}
void size2(t_info *info, int *x)
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
				*x+=1;
				while(tmp[i] && tmp[i] != ' ' && tmp[i] != '\n')
					i++;
			}
			i++;
		}
	}
	end(tmp, fd);
	return (close(fd), free(tmp));
}
void size(t_info *info, int *x, int *y)
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

void	put_pixel_on_map(t_info* info)
{
	start_put_pixel(info, info->info_map);
}


