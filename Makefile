NAME = rtv1
CC = gcc
RM = rm -f
LIB =  -L libft/ -lft -L utilsc/ -lutilsc -lm -lpthread -D_REENTRANT -lreadline $(shell sdl2-config --libs)
LIBFTDIR = libft
UTILSCDIR = utilsc
INCLUDE = -I utilsc/include -I include -I libft/includes $(shell sdl2-config --cflags)
CFLAGS = -pipe -Wall -Werror -Wextra $(INCLUDE)
SRC =	src/buffer.c \
		src/buffer_reload.c \
		src/buffer_ss.c \
		src/cam.c \
		src/cam_motion.c \
		src/cmd.c \
		src/cmd_display.c \
		src/cmd_load_obj.c \
		src/cmd_load_scene.c \
		src/cmd_mod_obj.c \
		src/cmd_mod_value.c \
		src/cmd_new_scene.c \
		src/cmd_read_scene.c \
		src/cmd_save_scene.c \
		src/color.c \
		src/light.c \
		src/light_handler.c \
		src/main.c \
		src/object.c \
		src/object_delet.c \
		src/object_error.c \
		src/quad.c \
		src/ray.c \
		src/ray_transform.c \
		src/raytrace.c \
		src/raytrace_progressbar.c \
		src/raytrace_render.c \
		src/scene.c \
		src/sdl.c \
		src/sdl_change_sample.c \
		src/sdl_event.c \
		src/sdl_render.c \
		src/surface_cone.c \
		src/surface_cylindre.c \
		src/surface_hyperboloid.c \
		src/surface_plane.c \
		src/surface_sphere.c \
		src/vec.c \
		src/vec_mat.c \
		src/vec_op.c \
		src/vec_transform.c

DEBUG =
OPTI =# -O2

OBJ = $(SRC:.c=.o)

all: OPTI += -O2
all: $(NAME)

opti: OPTI += -O2
opti: re

debug: DEBUG += debug
debug: CFLAGS += -g3
debug: $(NAME)

$(NAME): $(OBJ) $(UTILSCDIR) $(LIBFTDIR) 
	$(CC) $(OPTI) -o $(NAME) $(OBJ) $(CFLAGS) $(LIB)

%.o: %.c
	$(CC) $(OPTI) -o $@ -c $< $(CFLAGS)

$(LIBFTDIR): ft

ft:
	make -j -C $(LIBFTDIR)/ $(DEBUG)

$(UTILSCDIR): ut

ut:
	make -j -C $(UTILSCDIR)/ $(DEBUG)

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
