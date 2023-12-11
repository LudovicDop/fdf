#include "include/mlx.h"

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

/*Stockage des informations de la map dans une variable char*/
char	**get_line(int fd)
{
	char	*buffer;
	char	*read_line;
	char	**tab;	
	read_line = ft_calloc(1, 1);
	while (buffer)
	{
		buffer = ft_strdup(get_next_line(fd));
		read_line = ft_strjoin(read_line, buffer);
	}
	tab = ft_split(read_line, ' ');
	return (tab);
}

/*Ouverture du fichier .fdf*/
int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	
	return (fd);
	
}
void	put_pixel_on_map(mlx_image_t* img, mlx_t* mlx, char *path)
{
	int	fd;
	char	**tab;
	coord_t *coord;
	int	i;
	
	i = 0;
	coord->x = 0;
	coord->y = 0;
	coord->z = 0;
	/*Lecture de la map*/
	fd = open_file(path);
	/*Stockage des infos map dans ma variable read_line*/
	tab = get_line(fd);
	while (tab[i])
	{
		/*Ici je divise img->height et width afin de placer ma map au centre de la page*/
		mlx_put_pixel(img, coord->x + (img->width / 2), coord->y + (img->height / 2), 0xFF000000);
		if (tab[i][1] != '\n')
		{
			coord->x++;
		}
		else
		{
			coord->x = 0;
			coord->y++;
		}
		i++;
	}
	//mlx_resize_image(img, WIDTH * 3, HEIGHT * 3);
	while (*tab)
	{
		printf("%s",*tab);
		*tab++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		mlx_set_setting(MLX_MAXIMIZED, true);
		mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42FDF", true);
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
