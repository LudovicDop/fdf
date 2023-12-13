/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:18:53 by ldoppler          #+#    #+#             */
/*   Updated: 2023/12/13 13:19:05 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mlx.h"

int	main(int argc, char **argv)
{
	t_info	*info;

	if (!info)
		return (1);
	if (argc == 2)
	{
		info = ft_calloc(1, sizeof(t_info));
		if (!info)
			return (1);
		info->path = ft_strdup(argv[1]);
		init(info);
		init_loop_hook(info);
		put_pixel_on_map(info, info->path);
		mlx_loop(info->mlx);
		destroy_loop_hook(info);
	}
	return (0);
}
