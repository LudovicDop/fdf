MAKEFLAGS += --silent
SRC = ./src/drawing_bis.c ./src/drawing_bis2.c ./src/drawing_bis3.c ./src/drawing.c ./src/error.c ./src/hooks_feature.c ./src/hooks.c ./src/init_my_window.c ./src/main.c ./src/merge.c ./src/parsing.c ./src/tool.c
CC = gcc -fsanitize=address -Wall -Werror -Wextra 
NAME = fdf

all : $(NAME)

$(NAME):
	make -C libft/
	make -C gnl/
	cmake ./MLX42 -B ./MLX42/build && make -C ./MLX42/build -j4
	$(CC) $(SRC) gnl/gnl.a -L./libft -lft -L./MLX42 -lmlx42 -I./MLX42/include -I./ -ldl -lglfw -pthread -lm -o $(NAME)
	echo "Done ✅"
clean : 
	rm -rf *.a
	make clean -C libft/
	make clean -C gnl/ 
	rm -rf MLX42/build
	rm -rf $(OBJ)
	echo "Clean ✅ "
fclean : clean
	make fclean -C libft/
	make fclean -C gnl/
	rm -rf fdf
	echo "Fclean ✅"
re : fclean all $(NAME) 

.PHONY: all clean fclean re
