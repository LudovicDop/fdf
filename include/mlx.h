#ifndef MLX_H
# define MLX_H
# define WIDTH 1080
# define HEIGHT 1090
# include "../gnl/get_next_line.h"
# include "MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>

typedef struct s_info_map
{
	float			x;
	float			y;
	float			z;
	float			origin_x;
	float			origin_y;
	float			origin_z;
	unsigned int	color;
}					t_info_map;

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
	float			DEG_Y;
	float			DEG_Z;
	float			scale;
	float			rotation_angle_x;
	float			rotation_angle_y;
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

}					t_info;

typedef struct s_increase
{
	int				i;
	int				j;
	int				k;
	int				l;
	int				x;
	int				y;
}					t_increase;

typedef struct s_rot
{
	float			x0_rot;
	float			y0_rot;
	float			z0_rot;
}					t_rot;

typedef struct s_iso
{
	float			x0_iso;
	float			y0_iso;
	float			x1_iso;
	float			y1_iso;
}					t_iso;

void				ft_hook(void *param);
void				resize_img(mlx_image_t *img, unsigned int width,
						unsigned int height);
void				ft_hook_resize(int width, int height, void *param);
int					init(t_info *info);
void				init_loop_hook(t_info *info);
void				error(void);
void				destroy_loop_hook(t_info *info);
void				put_pixel_on_map(t_info *info);
int					open_file(char *path);
char				***ft_split_for_mlx(char *string);
void				free_my_tab(char **tab);
void				start_put_pixel(t_info *info, t_info_map *info_map);
void				size(t_info *info, int *x, int *y);
void				parse(t_info *info, t_info_map *info_map, int size);
unsigned int		hex_to_uint(const char *hex);
int					ft_strlen_int(int number);
void				start_put_pixel(t_info *info, t_info_map *info_map);
void				isometric_transform_and_draw_line(t_info *info,
						t_info_map *info_map, t_info_map *info_map2);
void				rotate_about_center(t_info_map *info_map, t_rot *rot,
						t_info *info);
void				rotate_about_center_bis(t_info *info, t_info_map *info_map,
						t_rot *rot);
void				isometric_transform(t_rot *rot, float *x_iso, float *y_iso,
						t_info *info);
void				link_pxl(t_info *info, t_iso *iso, unsigned int color);
void				more_v_than_h(t_info *info, t_iso *iso, unsigned int color);
void				more_h_than_v(t_info *info, t_iso *iso, unsigned int color);
void				horizontal_pxl(t_iso *iso, unsigned int color,
						t_info *info);
void				vertical_pxl(t_iso *iso, unsigned int color, t_info *info);
void				ft_hooks_s(t_info *info);
void				ft_hooks_d(t_info *info);
void				ft_hooks_x(t_info *info);
void				ft_hooks_a(t_info *info);
void				ft_hooks_c(t_info *info);
void				free_char_array(char **array);
void				parse3(t_info_map *info_map, t_increase *x, char **tmp);
void				parse2(char *buffer, t_info_map *info_map, int fd,
						int size);
void				parse(t_info *info, t_info_map *info_map, int size);
unsigned int	merge_rgba(unsigned int color1, unsigned int color2);
int abs(int x);
int sgn(int x);
#endif
