MAKEFLAGS += --silent
CC = gcc -Wall -Werror -Wextra
OBJ = $(libft:.c=.o) $(MLX42:.c=.o) $(gnl:.c=.o)
NAME = mlx.a
all : $(NAME)

.c.o :
	$(CC) -c $< -o $(<:.c=.o)
$(NAME) : $(OBJ)
	echo "Creation in progress..." 
	make -C libft/
	mv libft/libft.a .
	mv libft.a $(NAME)
	make -C MLX42/
	mv MLX42/libmlx42.a .
	mv libmlx42.a $(NAME)
	make -C gnl/
	mv gnl/gnl.a .
	mv gnl.a $(NAME)
	ar rcs $@ $(OBJ)
	echo "Done!"
clean :
	echo "clean in progress..."
	make clean -C libft/
	make clean -C gnl/ 
	rm -rf $(OBJ)
	echo "Done!"
fclean : clean
	echo "fclean in progress..."
	make fclean -C libft/
	make fclean -C gnl/
	make clean -C MLX42/
	rm -rf $(NAME)
	echo "Done!"
re : fclean all $(NAME)
