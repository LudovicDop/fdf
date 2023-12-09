#include "include/mlx.h"

void ft_hook(void* param)
{
	mlx_t*	mlx;

	mlx = param;
	// If we PRESS the 'J' key, print "Hello".
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}
