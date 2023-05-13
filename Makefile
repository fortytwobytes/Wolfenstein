CC			=	cc
CFLAGS		=	-fsanitize=address -g # -Wall -Wextra -Werror
RM			=	rm -rf
MKDIR		=	mkdir -p

COMPILING	:=	-I lib/MLX42/include
MLX42		:=	lib/MLX42
MLX_LIB = lib/MLX42/build/libmlx42.a

OS	        :=      $(shell uname -s)
ifeq ($(OS),Linux)
    LINKING     :=      $(MLX_LIB) -ldl -lglfw -pthread -lm
else
    LINKING     :=      $(MLX_LIB) -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
endif

SRCS		=	$(wildcard main.c lib/libc/*.c srcs/*.c srcs/parsing/*.c srcs/engine/*.c srcs/norm/*.c srcs/utils/*.c)

SRCS_DIRS   = $(dir $(SRCS))

BIN_DIR     = bin/

OBJS        = $(SRCS:%.c=$(BIN_DIR)%.o)
OBJS_DIRS   = $(dir $(OBJS))

INCLUDES	=	$(wildcard includes/*.h)

NAME		=	cub3D

all: $(NAME)

$(MLX_LIB):
	cmake $(MLX42) -B $(MLX42)/build
	make -C $(MLX42)/build -j4

$(NAME):    $(OBJS) $(MLX_LIB)
	@$(CC) $(CFLAGS) $^ $(LINKING) -o $@

$(BIN_DIR)%.o:  %.c $(INCLUDES) $(MLX_LIB)
	@$(MKDIR) $(OBJS_DIRS)
	$(CC) $(CFLAGS) $(COMPILING) -c $< -o $@

forb:
	@sh ./list_forb_functions.sh

clean:
	@$(RM) $(BIN_DIR) a.out
	@$(RM) $(basename $(wildcard tests/test_*.c) .c)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
