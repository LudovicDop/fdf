/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:37:50 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/03 16:39:46 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"

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



void isometric_transform(int x, int y, int z, int *x_iso, int *y_iso, t_info* info) {
    float radX = info->DEG_X * M_PI / 180;
    float radY = info->DEG_Y * M_PI / 180;

    *x_iso = (x - z) * cos(radX) * info->scale;
    *y_iso = (y + (x + z) * sin(radY)) * info->scale;
}


// void rotate_about_center(int x, int y, int z, int *x_rot, int *y_rot, int *z_rot, t_info *info) {
//     int center_x = 0/* calculer ou définir le centre x */;
//     int center_y = 0/* calculer ou définir le centre y */;
//     int center_z = 0/* calculer ou définir le centre z */;

//     // Décalage par rapport au centre
//     x -= center_x;
//     y -= center_y;
//     z -= center_z;

//     // Appliquer la rotation autour de l'axe X et Y
//     int temp_x = x * cos(info->rotation_angle) - y * sin(info->rotation_angle);
//     int temp_y = x * sin(info->rotation_angle) + y * cos(info->rotation_angle);

//     // Appliquer la rotation autour de l'axe Z
//     *x_rot = (temp_x * cos(info->z_rotation_angle) - z * sin(info->z_rotation_angle)) * info->scale;
//     *z_rot = (temp_x * sin(info->z_rotation_angle) + z * cos(info->z_rotation_angle)) * info->scale;
//     *y_rot = temp_y * info->scale;

//     // Réajustement par rapport au centre
//     *x_rot += center_x;
//     *y_rot += center_y;
//     *z_rot += center_z;
// }

void rotate_about_center(int x, int y, int z, int *x_rot, int *y_rot, int *z_rot, t_info *info) {
    float center_x = 99.5; // Define center x
    float center_y = 57.5; // Define center y
    float center_z = 0; // Define center z

    // Offset from center
    x -= center_x;
    y -= center_y;
    z -= center_z;

    // Rotate around X axis
    int temp_y = y * cos(info->rotation_angle_x) - z * sin(info->rotation_angle_x);
    int temp_z = y * sin(info->rotation_angle_x) + z * cos(info->rotation_angle_x);
    y = temp_y;
    z = temp_z;

    // Rotate around Y axis
    int temp_x = x * cos(info->rotation_angle_y) + z * sin(info->rotation_angle_y);
    temp_z = -x * sin(info->rotation_angle_y) + z * cos(info->rotation_angle_y);
    x = temp_x;
    z = temp_z;

    // Rotate around Z axis and apply scale
    temp_x = x * cos(info->rotation_angle_z) - y * sin(info->rotation_angle_z);
    temp_y = x * sin(info->rotation_angle_z) + y * cos(info->rotation_angle_z);
    x = temp_x * info->scale;
    y = temp_y * info->scale;
    z = temp_z * info->scale; // Apply scale to z if needed

    // Readjust with respect to center
    *x_rot = x + center_x;
    *y_rot = y + center_y;
    *z_rot = z + center_z;
}



void isometric_transform_and_draw_line(t_info* info, int x0, int y0, int z0, int x1, int y1, int z1) {
    int x0_rot, y0_rot, z0_rot, x1_rot, y1_rot, z1_rot;
    int x0_iso, y0_iso, x1_iso, y1_iso;

    // Appliquez la rotation autour du centre
    rotate_about_center(x0, y0, z0, &x0_rot, &y0_rot, &z0_rot, info);
    rotate_about_center(x1, y1, z1, &x1_rot, &y1_rot, &z1_rot, info);

    // Appliquez la transformation isométrique aux points de départ et de fin
    isometric_transform(x0_rot, y0_rot, z0_rot, &x0_iso, &y0_iso, info);
    isometric_transform(x1_rot, y1_rot, z1_rot, &x1_iso, &y1_iso, info);

    // Dessinez maintenant la ligne en utilisant les coordonnées isométriques
	if(x0_iso + info->img->width / 2 < info->img->width 
	&& y0_iso  + info->img->height / 2 < info->img->height 
	&& x1_iso  + info->img->width / 2 < info->img->width 
	&& y1_iso  + info->img->height / 2 < info->img->height)
    	link_pxl(info, x0_iso + info->img->width / 2, y0_iso  + info->img->height / 2, x1_iso + info->img->width / 2, y1_iso  + info->img->height / 2);
}

void	parse_my_map(t_info *info, char *tab, char *tmp, int fd)
{
	while (tmp)
	{
		tmp = get_next_line(fd);
		tab = ft_strjoin(tab, tmp);
	}
	info->tab2d = ft_split_for_mlx(tab);
	int i;
	int j;

	i = 0;
	j = 0;

	while (info->tab2d[i])
	{
		j = 0;
		while(info->tab2d[i][j])
		{
			printf("tab[%d][%d] = %s\n",i,j,info->tab2d[i][j]);
			j++;
		}
		i++;
	}
	free(tab);
	free(tmp);
}

void start_put_pixel(t_info* info)
{
	int  end;
	// char **z0;
	// char **z1;

	end = 0;
	while (info->tab2d[info->x0] && end != 1)
	{
		if (info->tab2d[info->x0 + 1])
		{
			//printf("ret[%d][%d] = %d\n",info->x0,info->y0,ft_atoi(info->tab2d[info->x0 + 1][info->y0]));
			// z0 = ft_split(info->tab2d[info->x0][info->y0],',');
			// z1 = ft_split(info->tab2d[info->x0 + 1][info->y0],',');
			//printf("z = %d z1 = %d\n",ft_atoi(info->tab2d[info->x0][info->y0]), ft_atoi(info->tab2d[info->x0 + 1][info->y0]));
			isometric_transform_and_draw_line(info, info->x0, info->y0,ft_atoi(info->tab2d[info->x0][info->y0]), (info->x0 + 1), info->y0, ft_atoi(info->tab2d[info->x0 + 1][info->y0]));
			// free_my_tab_2d(z0);
			// free_my_tab_2d(z1);
			if (info->tab2d[info->x0][info->y0 + 1])
			{
				// z0 = ft_split(info->tab2d[info->x0][info->y0],',');
				// z1 = ft_split(info->tab2d[info->x0 + 1][info->y0],',');
				isometric_transform_and_draw_line(info, info->x0 , info->y0,ft_atoi(info->tab2d[info->x0][info->y0]), info->x0 , (info->y0 + 1) , ft_atoi(info->tab2d[info->x0][info->y0 + 1]));
				// free_my_tab_2d(z0);
				// free_my_tab_2d(z1);
			}
			info->x0++;
		}
		else
		{
			if (info->tab2d[info->x0][info->y0 + 1])
			{
				// z0 = ft_split(info->tab2d[info->x0][info->y0],',');
				// z1 = ft_split(info->tab2d[info->x0 + 1][info->y0],',');
				isometric_transform_and_draw_line(info, info->x0 , info->y0 ,ft_atoi(info->tab2d[info->x0][info->y0]), info->x0 , (info->y0 + 1) , ft_atoi(info->tab2d[info->x0][info->y0 + 1]));
				// free_my_tab_2d(z0);
				// free_my_tab_2d(z1);
			}
			info->x0 = 0;
			if (info->tab2d[info->x0][info->y0 + 1])
				info->y0++;
			else
				end = 1;
		}
		info->refresh = 0;
	}
	free_my_tab(info->tab2d);
}

void	put_pixel_on_map(t_info* info, char *path)
{
	int		fd;
	char *tab;
	char *tmp;
	
	 //info->DEG_X = 0;
	 //info->DEG_Y = 0;
	//info->scale = 2.0;
	// info->DEG_Y = 0;
	//info->scale = 20;
	//info->rotation_angle = 380;
	tmp = ft_calloc(1, 1);
	if (!tmp)
		return ;
	tab = ft_calloc(1, 1);
	if (!tab)
		return ;
	fd = open_file(path);
	info->x0 = 0;
	info->y0 = 0;
	parse_my_map(info, tab, tmp, fd);
	start_put_pixel(info);
	free(tmp);
}


