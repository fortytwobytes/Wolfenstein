CC			=	cc
CFLAGS		=	-fsanitize=address # -Wall -Wextra -Werror
RM			=	rm -rf
MKDIR		=	mkdir -p

COMPILING	:=	-I MLX42/include

OS	        :=      $(shell uname -s)
ifeq ($(OS),Linux)
    LINKING     :=      MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm
else
    LINKING     :=      MLX42/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
endif

SRCS		=	$(wildcard main.c libc/*.c srcs/*.c)

SRCS_DIRS   = $(dir $(SRCS))

BIN_DIR     = bin/

OBJS        = $(SRCS:%.c=$(BIN_DIR)%.o)
OBJS_DIRS   = $(dir $(OBJS))

INCLUDES	=	$(wildcard libc/*.h srcs/*.h)

NAME		=	cub3D

all: $(NAME)

$(NAME):    $(OBJS)
	$(CC) $(CFLAGS) $^ $(LINKING) -o $@

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

