#include "include/mlx.h"

void ft_hook(void* param)
{
	mlx_t*	mlx;

	mlx = param;
	// If we PRESS the 'ESCAPE' key, it will close the window.
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}
