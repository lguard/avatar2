NAME = avatar2
CC = gcc -std=c11
RM = rm -f
LIB =  -L libft/ -lft -L utilsc/ -lutilsc -lm -lpthread -D_REENTRANT -lreadline $(shell sdl2-config --libs)
INCLUDE = -I utilsc/include -I include -I libft/includes $(shell sdl2-config --cflags)
CFLAGS = -pipe -Wall -Werror -Wextra $(INCLUDE)
SRC = $(addprefix src/, $(shell ls src | grep .c -F))
DEBUG =
OPTI = -O2

OBJ = $(SRC:.c=.o)

all: $(NAME)

opti: OPTI += -O2
opti: re

debug: DEBUG += debug
debug: CFLAGS += -g3
debug: re

$(NAME): $(OBJ)
	make -j -C utilsc $(DEBUG)
	make -j -C libft $(DEBUG)
	$(CC) $(OPTI) -o $(NAME) $(OBJ) $(CFLAGS) $(LIB)

%.o: %.c
	$(CC) $(OPTI) -o $@ -c $< $(CFLAGS)

clean:
	make -C utilsc clean
	make -C libft clean
	$(RM) $(OBJ)

fclean: clean
	make -C utilsc fclean
	make -C libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: re fclean clean all
