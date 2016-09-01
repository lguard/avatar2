NAME = avatar2
CC = gcc -std=c11
RM = rm -f
LIB =  -L utilsc/ -lutilsc -lm $(shell sdl2-config --libs)
INCLUDE = -I utilsc/include -I include $(shell sdl2-config --cflags)
CFLAGS = -pipe -Wall -Werror -Wextra $(INCLUDE)
SRC = $(addprefix src/, $(shell ls src | grep .c -F))
DEBUG =
OPTI = -O2

OBJ = $(SRC:.c=.o)

all: $(NAME)

opti: OPTI += -O2
opti: re

debug: DEBUG += debug
debug: CFLAGS += -g
debug: re

$(NAME): $(OBJ)
	make -j -C utilsc $(DEBUG)
	$(CC) $(OPTI) -o $(NAME) $(OBJ) $(CFLAGS) $(LIB)

%.o: %.c
	$(CC) $(OPTI) -o $@ -c $< $(CFLAGS)

clean:
	make -C utilsc clean
	$(RM) $(OBJ)

fclean: clean
	make -C utilsc fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: re fclean clean all
