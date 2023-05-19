CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf
MKDIR		=	mkdir -p

COMPILING	=	-I lib/MLX42/include
MLX42		=	lib/MLX42
MLX_LIB		=	lib/MLX42/build/libmlx42.a

OS	        =	$(shell uname -s)

ifeq ($(OS),Linux)
    LINKING =	$(MLX_LIB) -ldl -lglfw -pthread -lm
else
    LINKING =	$(MLX_LIB) -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
endif

SRCS		=	main.c lib/libc/fatal.c lib/libc/ft_atoi.c lib/libc/ft_calloc.c lib/libc/ft_memcpy.c lib/libc/ft_memset.c lib/libc/ft_split.c lib/libc/ft_strchr.c lib/libc/ft_strcmp.c lib/libc/ft_strdup.c lib/libc/ft_strlen.c lib/libc/ft_strrchr.c lib/libc/ft_strtrim.c lib/libc/ft_substr.c lib/libc/get_next_line.c lib/libc/split_utils.c srcs/inits.c srcs/parsing/parse_elements.c srcs/parsing/parse_map.c srcs/parsing/parse_utils.c srcs/parsing/parsing.c srcs/parsing/utils.c srcs/engine/hooks.c srcs/engine/minimap.c srcs/engine/minimap_utils.c srcs/engine/move.c srcs/engine/raycasting.c srcs/engine/textures.c srcs/engine/utils.c srcs/engine/view.c srcs/utils/drawing.c srcs/utils/helpers.c

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
	$(RM) $(MLX_LIB)

re: fclean all
