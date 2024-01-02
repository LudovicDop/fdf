#ifndef MLX_H
# define MLX_H
# define WIDTH 1080
# define HEIGHT 1090
# include "../gnl/get_next_line.h"
# include "MLX42/MLX42.h"
# include <stdio.h>
# include <math.h>
# define ABS(_x) ((_x) >= 0 ? (_x) : -(_x))
# define SGN(_x) ((_x) < 0 ? -1 : \
						 ((_x) > 0 ? 1 : 0))

typedef struct s_info
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			refresh;
	char		*path;
	char		***tab2d;
	int			x0;
	int			y0;
	int			z0;
	int			x1;
	int			y1;
	int			z1;
	int			DEG_X;
 	int 		DEG_Y;
	int 		DEG_Z;
	int 		temp_x0;
	int			x0_iso;
	int			y0_iso;
	int			x1_iso;
	int			y1_iso;
	int			temp_x1;
	int			temp_y1;
	int			temp_y0;
}				t_info;

typedef struct s_increase
{
	int	i;
	int j;
	int	k;
	int	l;
	int x;
	int y;
}				t_increase;

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
char    		***ft_split_for_mlx(char *string);
void    		free_my_tab(char ***tab);
#endif
