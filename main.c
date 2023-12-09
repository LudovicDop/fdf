#include "include/mlx.h"

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	main(void)
{
	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42FDF", false);
	if (!mlx)
		error();
	mlx_image_t* img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!img)
		error();
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		error();
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	int x = 0;
	while (x < mlx->width)
	{
		mlx_put_pixel(img, x, 10, 0xFF000000);
		x++;
	}
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
} 
