MAKEFLAGS += --silent
#CC = gcc -fsanitize=address -Wall -Werror -Wextra 
CC = gcc
NAME = mlx.a
all : $(NAME)

.c.o :
	$(CC) -c $< -o $(<:.c=.o)
$(NAME) : $(OBJ)
	echo "Creation in progress..." 
	make -C libft/
	mv libft/libft.a .
	cd MLX42/ && cmake -DDEBUG=1 -DGLFW_FETCH=0
	cd ..
	make -C MLX42/
	make -C gnl/
	mv gnl/gnl.a .
	$(CC) src/*.c -L. gnl.a -lft -LMLX42 -lmlx42 -IMLX42/include -I./ -ldl -lglfw -pthread -lm -o fdf
	echo "Done ✅"
clean : 
	echo "clean in progress..."
	rm -rf *.a
	make clean -C libft/
	make clean -C gnl/ 
	make clean -C MLX42/
	rm -rf $(OBJ)
	echo "Clean ✅ "
fclean : clean
	echo "fclean in progress..."
	make fclean -C libft/
	make fclean -C gnl/
	rm -rf ./MLX42/CMakeFiles ./MLX42/CMakeCache.txt 
	rm -rf fdf
	echo "Fclean ✅"
re : fclean all $(NAME) 
