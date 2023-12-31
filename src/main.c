/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:18:53 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/05 19:24:04 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"

int	main(int argc, char **argv)
{
	t_info	*info;

	if (argc == 2)
	{
		info = ft_calloc(1, sizeof(t_info));
		info->scale = 2.0;
		info->rotation_angle_x = 0;
		info->rotation_angle_y = 0;
		info->rotation_angle_z = 0;
		if (!info)
			return (1);
		info->path = ft_strdup(argv[1]);
		if (!info->path)
			return (free(info),1);
		init(info);
		init_loop_hook(info);
		put_pixel_on_map(info);
		mlx_loop(info->mlx);
		destroy_loop_hook(info);
	}
	return (0);
}
