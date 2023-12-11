#ifndef MLX_H
# define MLX_H
# define WIDTH 1080 
# define HEIGHT 1090
# include "MLX42/MLX42.h"
# include "../gnl/get_next_line.h"
# include <stdio.h>
typedef struct coord_s
{
	int x;
	int y;
	int z;
}coord_t;
void ft_hook(void* param);
#endif
