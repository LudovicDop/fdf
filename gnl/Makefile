Part1 = get_next_line.c get_next_line_utils.c
CC = gcc
CFLAGS = -Wall -Werror -Wextra
OBJ = $(Part1:.c=.o)
NAME = gnl.a

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	ar rcs $@ $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

.PHONY: all clean fclean

