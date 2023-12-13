#ifndef MLX_H
# define MLX_H
# define WIDTH 1080
# define HEIGHT 1090
# include "../gnl/get_next_line.h"
# include "MLX42/MLX42.h"
# include <stdio.h>

typedef struct s_info
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			refresh;
	char		*path;
}				t_info;

typedef struct coord_s
{
	int			x;
	int			y;
	int			z;
}				coord_t;

void			ft_hook(void *param);
void			resize_img(mlx_image_t *img, unsigned int width,
					unsigned int height);
void			ft_hook_resize(int width, int height, void *param);
int				init(t_info *info);
void			init_loop_hook(t_info *info);
void			error(void);
void			destroy_loop_hook(t_info *info);
void			put_pixel_on_map(t_info* info, char *path);
int				open_file(char *path);
#endif
