CC			=	cc
CFLAGS		=	-fsanitize=address -g # -Wall -Wextra -Werror
RM			=	rm -rf
MKDIR		=	mkdir -p

COMPILING	:=	-I lib/MLX42/include

OS	        :=      $(shell uname -s)
ifeq ($(OS),Linux)
    LINKING     :=      lib/MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm
else
    LINKING     :=      lib/MLX42/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
endif

SRCS		=	$(wildcard main.c lib/libc/*.c srcs/*.c srcs/parsing/*.c srcs/engine/*.c srcs/norm/*.c srcs/utils/*.c)

SRCS_DIRS   = $(dir $(SRCS))

BIN_DIR     = bin/

OBJS        = $(SRCS:%.c=$(BIN_DIR)%.o)
OBJS_DIRS   = $(dir $(OBJS))

INCLUDES	=	$(wildcard includes/*.h)

NAME		=	cub3D

all: $(NAME)

$(NAME):    $(OBJS)
	@$(CC) $(CFLAGS) $^ $(LINKING) -o $@

$(BIN_DIR)%.o:  %.c $(INCLUDES)
	@$(MKDIR) $(OBJS_DIRS)
	$(CC) $(CFLAGS) $(COMPILING) -c $< -o $@

test: re
	@make -C tests/

forb:
	@sh ./list_forb_functions.sh

clean:
	@$(RM) $(BIN_DIR) a.out
	@$(RM) $(basename $(wildcard tests/test_*.c) .c)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

