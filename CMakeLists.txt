cmake_minimum_required(VERSION 3.25)

set(CMAKE_C_STANDARD 99)

project(Cub3D)

set(LIBC
		lib/libc/fatal.c
		lib/libc/ft_atoi.c
		lib/libc/ft_calloc.c
		lib/libc/ft_memcpy.c
		lib/libc/ft_memset.c
		lib/libc/ft_split.c
		lib/libc/ft_strchr.c
		lib/libc/ft_strcmp.c
		lib/libc/ft_strdup.c
		lib/libc/ft_strlen.c
		lib/libc/ft_strrchr.c
		lib/libc/ft_strtrim.c
		lib/libc/ft_substr.c
		lib/libc/get_next_line.c
		lib/libc/split_utils.c)

set(SRCS
		srcs/inits.c
		srcs/parsing/parse_elements.c
		srcs/parsing/parse_map.c
		srcs/parsing/parse_utils.c
		srcs/parsing/parsing.c
		srcs/parsing/utils.c
		srcs/engine/hooks.c
		srcs/engine/minimap.c
		srcs/engine/minimap_utils.c
		srcs/engine/move.c
		srcs/engine/raycasting.c
		srcs/engine/textures.c
		srcs/engine/utils.c
		srcs/engine/view.c
		srcs/utils/drawing.c
		srcs/utils/helpers.c)

# Compile the MLX42 library
add_custom_target(mlx42_library
		COMMAND cmake -B ${CMAKE_SOURCE_DIR}/lib/MLX42/build ${CMAKE_SOURCE_DIR}/lib/MLX42
		COMMAND cmake --build ${CMAKE_SOURCE_DIR}/lib/MLX42/build -j4
		)

add_executable(cub3D main.c ${LIBC} ${SRCS})

# add includes
target_include_directories(cub3D PUBLIC includes)

# add libraries
target_link_libraries(cub3D PUBLIC ${CMAKE_SOURCE_DIR}/lib/MLX42/build/libmlx42.a)
if (UNIX)
	target_link_libraries(cub3D PUBLIC dl glfw pthread m)
else ()
	target_link_libraries(cub3D PUBLIC glfw "/Users/${USER}/.brew/opt/glfw/lib")
endif ()

# add flags
target_compile_options(cub3D PUBLIC -Wall -Wextra -Werror)

# Ensure the MLX42 library is built before building the cub3D executable
add_dependencies(cub3D mlx42_library)
