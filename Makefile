CC			=	cc
CFLAGS		=	# -fsanitize=address # -Wall -Wextra -Werror
RM			=	rm -rf
MKDIR		=	mkdir -p
# MLX_FLAGS  	=   -Imlx -lmlx -framework OpenGL -framework AppKit

SRCS		=	$(wildcard main.c libc/*.c srcs/*.c)

SRCS_DIRS   = $(dir $(SRCS))

BIN_DIR     = bin/

OBJS        = $(SRCS:%.c=$(BIN_DIR)%.o)
OBJS_DIRS   = $(dir $(OBJS))

INCLUDES	=	$(wildcard libc/*.h srcs/*.h)

NAME		=	cub3D

all: $(NAME)

$(NAME):    $(OBJS)
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $^ -o $@

$(BIN_DIR)%.o:  %.c $(INCLUDES)
	@$(MKDIR) $(OBJS_DIRS)
	@$(CC) $(CFLAGS) -c $< -o $@

test: all
	@make -C tests/

clean:
	@$(RM) $(BIN_DIR)
	@$(RM) $(basename $(wildcard tests/test_*.c) .c)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

