#include "include/mlx.h"

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	put_pixel_on_map(mlx_image_t* img, mlx_t* mlx, char *path)
{
	int	fd;
	char	*read_line;
	char	*buffer;
	char	**tab;

	fd = open(path, O_RDONLY);
	read_line = ft_calloc(1, 1);
	while (buffer)
	{
		buffer = ft_strdup(get_next_line(fd));
		read_line = ft_strjoin(read_line, buffer);
	}
	printf("%s",read_line);
	tab = ft_split(read_line, ' ');
	int i = 0;
	int y = 0;
	int x = 0;
	while (tab[i])
	{
		mlx_put_pixel(img, x, y, 0xFF000000);
		if (tab[i][1] != '\n')
		{
			x++;
		}
		else
		{
			x = 0;
			y++;
		}
		i++;
		printf("ok");
	}
	printf("ok");
}

int	main(int argc, char **argv)
{
	if (argc == 2)
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
		put_pixel_on_map(img, mlx, argv[1]);
		mlx_loop_hook(mlx, ft_hook, mlx);
		mlx_loop(mlx);
		mlx_delete_image(mlx, img);
		mlx_terminate(mlx);
		return (EXIT_SUCCESS);
	}
	return (0);
} 
