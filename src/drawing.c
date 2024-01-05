/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:37:50 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/05 19:41:43 by ludovicdopp      ###   ########.fr       */
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

char	*remove_space(char *string)
{
	int		i;
	int		k;
	char	*ret;

	k = 0;
	i = 0;
	while (string[i])
	{
		if (string[i] != ' ')
			k++;
		i++;
	}
	ret = malloc(sizeof(char) * k + 1);
	i = 0;
	k = 0;
	while (string[i])
	{
		if (string[i] != ' ')
		{
			ret[k] = string[i];
			k++;
		}
		i++;
	}
	ret[k] = '\0';
	return (free(string), ret);
}

void link_pxl(t_info* info, int x0, int y0, int x1, int y1)
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
					mlx_put_pixel(info->img, x,y0, 0xFFFFFFFF);
			}
			else if (dx == 0)
			{
				// vertical line
				for (int y = y0; y != y1 + incY; y += incY)
					mlx_put_pixel(info->img, x0,y, 0xFFFFFFFF);
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
					mlx_put_pixel(info->img, x,y, 0xFFFFFFFF);
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
					mlx_put_pixel(info->img, x,y, 0xFFFFFFFF);
					error += slope;

					if (error >= 0)
					{
						x += incX;
						error += errorInc;
					}
				}
			}
}



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

    // Offset from center
    x -= center_x;
    y -= center_y;
    z -= center_z;

    // Rotate around X axis
    float temp_y = y * cosf(info->rotation_angle_x) - z * sinf(info->rotation_angle_x);
    float temp_z = y * sinf(info->rotation_angle_x) + z * cosf(info->rotation_angle_x);
    y = temp_y;
    z = temp_z;

    // Rotate around Y axis
    float temp_x = x * cosf(info->rotation_angle_y) + z * sinf(info->rotation_angle_y);
    temp_z = -x * sinf(info->rotation_angle_y) + z * cosf(info->rotation_angle_y);
    x = temp_x;
    z = temp_z;

    // Rotate around Z axis and apply scale
    temp_x = x * cosf(info->rotation_angle_z) - y * sinf(info->rotation_angle_z);
    temp_y = x * sinf(info->rotation_angle_z) + y * cosf(info->rotation_angle_z);
    x = temp_x * info->scale;
    y = temp_y * info->scale;
    z = temp_z; // Apply scale to z if needed

    // Readjust with respect to center
    *x_rot = x + center_x;
    *y_rot = y + center_y;
    *z_rot = z + center_z;
}

void isometric_transform_and_draw_line(t_info* info, float x0, float y0, float z0, float x1, float y1, float z1) {
    float x0_rot, y0_rot, z0_rot, x1_rot, y1_rot, z1_rot;
    float x0_iso, y0_iso, x1_iso, y1_iso;

    // Apply rotation around the center
    rotate_about_center(x0, y0, z0, &x0_rot, &y0_rot, &z0_rot, info);
    rotate_about_center(x1, y1, z1, &x1_rot, &y1_rot, &z1_rot, info);

    // Apply isometric transformation to start and end points
    isometric_transform(x0_rot, y0_rot, z0_rot, &x0_iso, &y0_iso, info);
    isometric_transform(x1_rot, y1_rot, z1_rot, &x1_iso, &y1_iso, info);

    // Adjust for the center of the image
    x0_iso += info->img->width / 2;
    y0_iso += info->img->height / 2;
    x1_iso += info->img->width / 2;
    y1_iso += info->img->height / 2;

    // Check if the coordinates are within the bounds of the image
    if (x0_iso >= 0 && x0_iso < info->img->width && y0_iso >= 0 && y0_iso < info->img->height &&
        x1_iso >= 0 && x1_iso < info->img->width && y1_iso >= 0 && y1_iso < info->img->height) {
        // Draw the line using isometric coordinates
        link_pxl(info, x0_iso, y0_iso, x1_iso, y1_iso);
    }
}


// void	parse_my_map(t_info *info, char *tab, char *tmp, int fd)
// {
// 	while (tmp)
// 	{
// 		tmp = get_next_line(fd);
// 		tab = ft_strjoin(tab, tmp);
// 	}

// 	info->tab2d
	// info->tab2d = ft_split_for_mlx(tab);
	// int i;
	// int j;

	// i = 0;
	// j = 0;

	// while (info->tab2d[i])
	// {
	// 	j = 0;
	// 	while(info->tab2d[i][j])
	// 	{
	// 		//printf("tab[%d][%d] = %s\n",i,j,info->tab2d[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// }
// 	free(tab);
// 	free(tmp);
// }

//isometric_transform_and_draw_line
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
			{
				//printf("1) info[%d][%d] && info[%d][%d]\n",info_map[i].x,info_map[i].y,info_map[i + 1].x,info_map[i + 1].y);
				isometric_transform_and_draw_line(info, info_map[i].x, info_map[i].y, info_map[i].z, info_map[i + 1].x, info_map[i + 1].y, info_map[i + 1].z);
			}
			if (info_map[i].y < info->height - 1)
			{
				//printf("2) info[%d][%d] && info[%d][%d]\n",info_map[i].x,info_map[i].y,info_map[i + info->width].x,info_map[i + info->width].y);
				isometric_transform_and_draw_line(info, info_map[i].x, info_map[i].y, info_map[i].z, info_map[i + info->width].x, info_map[i + info->width].y, info_map[i + info->width].z);
			}
			printf("\n");
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

// void free_my_tab(char **tab)
// {
// 	int	i;
// 	int j;

// 	j = 0;
// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);

// }
void	parse(t_info* info, t_info_map *info_map, int size)
{
	int	fd;
	int i;
	int j;
	int y;
	char	**tmp;
	char *buffer;

	j = 0;
	i = 0;
	y = 0;
	fd = open_file(info->path);
	//buffer = ft_calloc(1, 1);
	buffer = get_next_line(fd);
	info_map[0].x = 0;
	info_map[0].y = 0;
	while (buffer)
	{
		//printf("%s\n",buffer);
		tmp = ft_split(buffer, ' ');
		if (!tmp)
			return (free(buffer));
		i = 0;
		info_map[j].x = -1;
		while (tmp[i] && j < size)
		{
			info_map[j].color = ft_strchr(tmp[i], ',');
			info_map[j].z = ft_atoi(tmp[i]);
			info_map[j].x = i;
			info_map[j].y = y;
			i++;
			j++;
		}
		y++;
		buffer = get_next_line(fd);
	}
}

void size(t_info *info, int *x, int *y)
{
	int		fd;
	int		i;
	char	*tmp;

	fd = open_file(info->path);
	tmp = ft_calloc(1, 1);
	i = 0;
	while (tmp)
	{
		tmp = get_next_line(fd);
		*y += 1;
	}
	get_next_line(fd);
	close(fd);
	free(tmp);
	fd = open_file(info->path);
	tmp = ft_calloc(1, 1);
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
	while (tmp)
	{
		tmp = get_next_line(fd);
	}
	close(fd);
	free(tmp);
}

void	put_pixel_on_map(t_info* info)
{
	// t_info_map *info_map;
	// int			x;
	// int			y;

	// x = 0;
	// y = -1;
	// size(info, &x, &y);
	// printf("x = %d && y = %d\n", x, y);
	// //info->points = ft_calloc
	// info_map = ft_calloc(x * y, sizeof(t_info_map));
	//parse(info, info_map, x * y);
	// info->height = y;
	// info->width = x;
	//printf("x = %d y = %d z = %d color = %s\n",info_map[INDEX].x,info_map[INDEX].y,info_map[INDEX].z,info_map[INDEX].color);
	start_put_pixel(info, info->info_map);
	//free(info_map);
}


