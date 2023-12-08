#include "MLX42/MLX42.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>

int	main(void)
{
	int fd = open("test_maps/42.fdf", O_RDONLY);
	printf("%s", get_next_line(fd));
	return (0);
} 
