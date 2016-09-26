NAME = libutilsc.a
CC = gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra
OPTI = -O2
SRC =	src/list.c \
		src/list_del.c

OBJ = $(SRC:.c=.o)
all: $(NAME)

debug: CFLAGS += -g3
debug: $(NAME)

dtest: CFLAGS += -g
dtest: test

test: clean $(NAME)
	$(CC) $(OPTI) -o test.exe  $(TEST) -I include -L . -l utilsc $(CFLAGS)

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
