# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/08 14:35:57 by ugdaniel          #+#    #+#              #
#    Updated: 2021/02/10 12:52:03 by ugdaniel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	./main.c ./game.c ./cub3d.c ./save_frame.c \
				./engine/window.c ./engine/draw.c ./engine/screen.c ./engine/camera.c \
				./engine/raycast.c ./engine/shortcut.c ./engine/draw_wall.c ./engine/ui.c \
				./engine/color.c ./engine/draw_sky_floor.c ./engine/calculate.c \
				./engine/texture.c ./engine/sprite.c ./engine/sprite_utils.c \
				./config/config.c ./config/map.c ./config/parse_params.c \
				./config/check_map.c ./config/parse_textures.c \
				./utils/ft_strlen.c ./utils/ft_strncmp.c ./utils/ft_strnstr.c \
				./utils/t_str.c ./utils/ft_strdup.c ./utils/pos.c ./utils/char_in_str.c \
				./utils/ft_atoi.c ./utils/ft_memmove.c ./utils/ft_substr.c \
				./gnl/get_next_line.c ./gnl/get_next_line_utils.c
OBJS		=	$(SRCS:.c=.o)

RM			=	rm -f

#CC			=	clang
#CFLAGS		=	-Wall -Wextra -Werror -I. -fsanitize=address

#MLX		=	libmlx.a
#LIBS		=	$(MLX) -lm -framework OpenGL -framework AppKit

CC			= clang
FLAGS		= -Wall -Werror -Wextra

MLX			= ./minilibx-linux/libmlx.a
MLXLINUX	= ./minilibx-linux/libmlx_Linux.a

NAME		=	Cub3D


all: $(NAME)

#$(NAME): $(MLX) $(OBJS)
#	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(NAME): $(OBJS)
	@make -s do_configure -C minilibx-linux -f Makefile
	${CC} ${OBJS} $(HEADERS) $(MLX) $(MLXLINUX) -L minilibx-linux -lX11 -lXext -lm -o $(NAME) -fsanitize=address
	@echo "Cub3d done"

$(MLX):
	@make -C mlx
	@mv mlx/$(MLX) .

clean:
	@make -C mlx clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(MLX)

re: fclean all

.PHONY: all clean fclean re
