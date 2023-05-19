CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf
MKDIR		=	mkdir -p

COMPILING	=	-I ../MLX42/include
MLX42		=	../MLX42
MLX_LIB		=	../MLX42/build/libmlx42.a

OS	        =	$(shell uname -s)

ifeq ($(OS),Linux)
    LINKING =	$(MLX_LIB) -ldl -lglfw -pthread -lm
else
    LINKING =	$(MLX_LIB) -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
endif

SRCS		=	main.c libc/fatal.c libc/ft_atoi.c libc/ft_calloc.c libc/ft_memcpy.c libc/ft_memset.c libc/ft_split.c libc/ft_strchr.c libc/ft_strcmp.c libc/ft_strdup.c libc/ft_strlen.c libc/ft_strrchr.c libc/ft_strtrim.c libc/ft_substr.c libc/get_next_line.c libc/split_utils.c srcs/inits.c srcs/parsing/parse_elements.c srcs/parsing/parse_map.c srcs/parsing/parse_utils.c srcs/parsing/parsing.c srcs/parsing/utils.c srcs/engine/hooks.c srcs/engine/minimap.c srcs/engine/minimap_utils.c srcs/engine/move.c srcs/engine/raycasting.c srcs/engine/textures.c srcs/engine/utils.c srcs/engine/view.c srcs/utils/drawing.c srcs/utils/helpers.c srcs/engine/mouse.c

SRCS_DIRS   = $(dir $(SRCS))

BIN_DIR     = bin/

OBJS        = $(SRCS:%.c=$(BIN_DIR)%.o)
OBJS_DIRS   = $(dir $(OBJS))

INCLUDES	=	includes/libc.h includes/srcs.h

NAME		=	cub3D

all: $(NAME)

$(MLX_LIB):
	@cmake $(MLX42) -B $(MLX42)/build
	@make -C $(MLX42)/build -j4

$(NAME):    $(OBJS) $(MLX_LIB)
	@$(CC) $(CFLAGS) $^ $(LINKING) -o $@

$(BIN_DIR)%.o:  %.c $(INCLUDES) $(MLX_LIB)
	@$(MKDIR) $(OBJS_DIRS)
	$(CC) $(CFLAGS) $(COMPILING) -c $< -o $@

clean:
	$(RM) $(BIN_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
