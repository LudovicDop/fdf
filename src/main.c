/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:18:53 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/02 22:21:57 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"

int	main(int argc, char **argv)
{
	t_info	*info;

	if (argc == 2)
	{
		info = ft_calloc(1, sizeof(t_info));
		if (!info)
			return (1);
		info->path = ft_strdup(argv[1]);
		if (!info->path)
			return (free(info),1);
		init(info);
		init_loop_hook(info);
		put_pixel_on_map(info, info->path);
		mlx_loop(info->mlx);
		destroy_loop_hook(info);
	}
	return (0);
}
