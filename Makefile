MAKEFLAGS += --silent
CC = gcc -Wall -Werror -Wextra
NAME = mlx.a
all : $(NAME)

.c.o :
	$(CC) -c $< -o $(<:.c=.o)
$(NAME) : $(OBJ)
	echo "Creation in progress..." 
	make -C libft/
	mv libft/libft.a .
	make -C MLX42/
	make -C gnl/
	mv gnl/gnl.a .
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
	rm -rf *.a
	echo "Done!"
re : fclean all $(NAME) 
