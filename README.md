# FDF

## Useful commands
- cmake -DDEBUG=1 -DGLFW_FETCH=0 (first time MLX42)
- make
- gcc src/*.c -L. gnl.a -lft -LMLX42 -lmlx42 -IMLX42/include -I./ -ldl -lglfw -pthread -lm
