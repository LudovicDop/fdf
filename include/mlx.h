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


typedef struct s_info_map
{
	int	x;
	int	y;
	int z;
	unsigned int color;
}	t_info_map;

typedef struct s_info
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_info_map	*info_map;
	int			refresh;
	int			height;
	int			width;
	char		*path;
	char		***tab2d;
	int			x0;
	int			y0;
	int			z0;
	int			x1;
	int			y1;
	int			z1;
	float			DEG_X;
 	float 		DEG_Y;
	float 		DEG_Z;
	int 		temp_x0;
	int			x0_iso;
	int			y0_iso;
	int			x1_iso;
	int			y1_iso;
	int			temp_x1;
	int			temp_y1;
	int			temp_y0;
	float			scale;
	float			rotation_angle_x;
	float 		rotation_angle_y;
	float			rotation_angle_z;
	float			z_rotation_angle;
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

typedef struct s_rot
{
	float x0_rot;
	float y0_rot;
	float z0_rot;
	float x1_rot;
	float y1_rot;
	float z1_rot;
}	t_rot;

typedef struct s_iso
{
	float x0_iso;
	float y0_iso;
	float x1_iso; 
	float y1_iso;
}	t_iso;


void			ft_hook(void *param);
void			resize_img(mlx_image_t *img, unsigned int width,
					unsigned int height);
void			ft_hook_resize(int width, int height, void *param);
int				init(t_info *info);
void			init_loop_hook(t_info *info);
void			error(void);
void			destroy_loop_hook(t_info *info);
void			put_pixel_on_map(t_info* info);
int				open_file(char *path);
char    		***ft_split_for_mlx(char *string);
void    		free_my_tab(char **tab);
void 			free_my_tab_2d(char **tab);
void start_put_pixel(t_info* info, t_info_map* info_map);
void size(t_info *info, int *x, int *y);
void	parse(t_info* info, t_info_map *info_map, int size);
#endif
