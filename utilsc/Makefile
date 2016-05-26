NAME = utilsc.a
CC = clang
RM = rm -f
CFLAGS = -Wall -Werror -Wextra
OPTI = -O2
OBJ = $(SRC:.c=.o)
SRC = $(addprefix src/, $(shell ls src | grep .c -F))
TEST = $(addprefix src/, $(shell ls test | grep .c -F))

all: $(NAME)

debug: CFLAGS += -g
debug: $(NAME)

dtest: CFLAGS += -g
dtest: test

test: $(NAME)
	$(CC) $(OPTI) -o test  $(TEST)-I include $(CFLAGS)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(OPTI) -o $@ -c $< -I include $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all 

.PHONY: re fclean clean all
