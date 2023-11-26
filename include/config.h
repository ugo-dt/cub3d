/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:11:09 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/26 15:32:08 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "utils.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <unistd.h>

# define CUB_LAST		9
# define CUB_R			0
# define CUB_NO			1
# define CUB_SO			2
# define CUB_WE			3
# define CUB_EA			4
# define CUB_S			5
# define CUB_F			6
# define CUB_C			7
# define CUB_MAP		8

# define DIRECTIONS				"NSEW"
# define VALID_MAP_CHARACTERS	" 01234NSEW"

# define TEXTURES		7
# define TEX_NORTH		0
# define TEX_SOUTH		1
# define TEX_WEST		2
# define TEX_EAST		3
# define TEX_SPRITE		4
# define TEX_FLOOR		5
# define TEX_SKY		6

typedef struct	s_options
{
	int		shadows;
	int		screenshot;
	int		update;
}				t_options;

typedef struct	s_config
{
	int			usr_width;
	int			usr_height;
	int			*map;
	int			map_size;
	int			rows;
	int			columns;
	int			set[CUB_LAST];
	double		rotate_speed;
	double		move_speed;
	double		fov;
	t_options	options;
	t_str		*map_buffer;
	unsigned	color[TEXTURES];
	char		*tex_path[TEXTURES];
}				t_config;

typedef struct	s_camera
{
	t_pos	pos;
	t_pos	dir;
	t_pos	x_dir;
	t_pos	plane;
}				t_camera;

void			init_config(t_config *config);
void			clear_config(t_config *config);

int				parse_config(
				t_config *config, t_camera *camera, char *file_path);
int				parse_dimensions(t_config *config, char const *line);
int				parse_color(t_config *config, int key, char const *line);

int				parse_map(
				t_config *config, t_str *map_buffer, t_camera *camera);
int				check_valid(
				t_config *config, t_str *map_buffer, t_camera *camera);
void			player_pos_angle(
				t_config *config, char dir, t_pos *pos, t_camera *camera);

int				parse_textures(t_config *config, int key, const char *line);

#endif

/*
**  CONFIG_H
*/
