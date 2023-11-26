# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/08 14:35:57 by ugdaniel          #+#    #+#              #
#    Updated: 2023/11/26 16:19:02 by ugdaniel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
OSTYPE = $(shell uname)

SRCS = $(wildcard srcs/*.c srcs/*/*.c)
OBJS = $(SRCS:.c=.o)

CC = @clang
FLAGS = -Wall -Wextra -Werror

LIBFT_PATH = lib/libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBS = $(LIBFT) -lm -Imlx

MLX_PATH = lib/mlx/$(OSTYPE)

INCLUDE = -I include -I $(LIBFT_PATH)/include

ifeq ($(OSTYPE),Linux)
	MLX_PATH = lib/mlx/linux
	MLX = $(MLX_PATH)/libmlx.a
	LIBS += $(MLX) -L $(MLX_PATH) -lXext -lX11
	INCLUDE += -I lib/mlx/linux
	FLAGS += -DLINUX
else
	MLX_PATH = lib/mlx/darwin
	MLX = $(MLX_PATH)/libmlx.a
	LIBS += $(MLX) -framework OpenGL -framework AppKit
	INCLUDE += -I lib/mlx/darwin
endif

white = \033[39m
green = \033[92m
cyan = \033[96m
magenta = \033[35m
lmagenta = \033[95m
yellow = \033[33m
gray = \033[37m
red = \033[91m
blue = \033[94m

all: $(NAME)
	@echo "$(green)$(NAME) ready!"
	@echo "$(white)\c"

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	@echo "$(yellow)Source files compiled"
	@echo "$(red)\c"
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBS)

.c.o:
	@echo "$(gray)Compiling $<... \c"
	@echo "$(red)\c"
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(cyan)OK!"

$(MLX):
	@echo "$(gray)Compiling MiniLibX... \c"
	@make -s -C $(MLX_PATH)
	@echo "$(cyan)OK!\n"
	clear
	@echo "$(green)MiniLibX compiled"
	@echo "$(red)\c"

$(LIBFT):
	@echo "$(gray)Compiling Libft... \c"
	@make -s -C $(LIBFT_PATH)
	@echo "$(cyan)OK!\n$(green)Libft compiled"
	@echo "$(red)\c"

clean_libft:
	@echo "$(gray)Cleaning Libft"
	@make -s clean -C $(LIBFT_PATH)

clean_mlx:
	@echo "$(gray)Cleaning MiniLibX"
	@make -s clean -C $(MLX_PATH)

fclean_mlx: clean_mlx
	@rm -f $(MLX)
	@echo "$(magenta)$(MLX) removed"

clean_objs:
	@echo "$(gray)Cleaning object files"
	@echo "$(red)\c"
	@rm -rf $(OBJS)

clean: clean_mlx clean_libft clean_objs

fclean_exec: clean_objs
	@rm -rf $(NAME)
	@echo "$(lmagenta)Executable removed"
	@echo "$(red)\c"

fclean_libft: clean_libft
	@rm -rf $(LIBFT)
	@echo "$(magenta)$(LIBFT) removed"
	@echo "$(red)\c"

fclean: fclean_mlx fclean_libft fclean_exec

re_nolib: fclean_exec newline all

re: fclean newline all clean_objs

newline:
	@echo ""

.PHONY: all clean_mlx clean_libft clean_objs clean fclean_exec fclean_libft fclean re_nolib re