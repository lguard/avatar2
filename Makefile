NAME = avatar2
CC = gcc
RM = rm -f
LIB =  -L utilsc/ -lutilsc -I utilsc/include
SDL = $(shell ~/.brew/Cellar/sdl2/2.0.4/bin/sdl2-config --libs) $(shell ~/.brew/Cellar/sdl2/2.0.4/bin/sdl2-config --cflags)
CFLAGS = -pipe -I ./include
SRC = $(addprefix src/, $(shell ls src | grep .c -F))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -j -C utilsc
	$(CC) -O2 $(CFLAGS) $(LIB) $(SDL) -o $(NAME) $(OBJ) 

%.o: %.c
	$(CC) -O2 -o $@ -c $< $(CFLAGS) -I utilsc/include $(shell ~/.brew/Cellar/sdl2/2.0.4/bin/sdl2-config --cflags)

clean:
	make -C utilsc clean
	$(RM) $(OBJ)

fclean: clean
	make -C utilsc fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: re fclean clean all
