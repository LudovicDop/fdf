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
	float	x;
	float	y;
	float z;
	float origin_x;
	float origin_y;
	float origin_z;
	unsigned int color;
}	t_info_map;

typedef struct s_info
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_info_map		*info_map;
	int				refresh;
	int				height;
	int				width;
	char			*path;
	float			DEG_X;
 	float 			DEG_Y;
	float 			DEG_Z;
	float			scale;
	float			rotation_angle_x;
	float 			rotation_angle_y;
	float			rotation_angle_z;
	float			z_rotation_angle;
	float			center_x;
	float			center_y;
	float			center_z;
	float			temp_x;
	float			temp_y;
	float			temp_z;
	int				dx;
	int				dy;
	int				incX;
	int				incY;
	int				slope;
	int				error;
	int				error_inc;
	int				x;
	int				y;

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
