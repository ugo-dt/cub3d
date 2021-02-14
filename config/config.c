/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:21:44 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/02/10 12:56:50 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

#define NO_FILE "No such file or directory\n"

void		init_config(t_config *config)
{
	int		i;

	config->usr_width = 848;
	config->usr_height = 480;
	config->map = NULL;
	config->rows = 0;
	config->columns = 0;
	config->rotate_speed = .06;
	config->move_speed = .03;
	config->fov = .66;
	config->options.shadows = 1;
	config->options.update = 1;
	i = 0;
	while (i < TEXTURES)
		config->tex_path[i++] = NULL;
	config->color[TEX_NORTH] = 0xFFFFFF;
	config->color[TEX_SOUTH] = 0xCCCCCC;
	config->color[TEX_WEST] = 0xFF44FF;
	config->color[TEX_EAST] = 0x44FF44;
	config->color[TEX_SKY] = 0x33C6E3;
	config->color[TEX_FLOOR] = 0xA0764C;
	i = 0;
	while (i < CUB_LAST)
		config->set[i++] = 0;
}

void		clear_config(t_config *config)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
	{
		if (config->tex_path[i])
			free(config->tex_path[i]);
		config->tex_path[i] = NULL;
		i++;
	}
	if (config->map)
		free(config->map);
	config->map = NULL;
	if (config->map_buffer)
		t_str_clear(&config->map_buffer);
}

static int	config_key(char const *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (CUB_R);
	else if (line[0] == 'N' && line[1] == 'O')
		return (CUB_NO);
	else if (line[0] == 'S' && line[1] == 'O')
		return (CUB_SO);
	else if (line[0] == 'W' && line[1] == 'E')
		return (CUB_WE);
	else if (line[0] == 'E' && line[1] == 'A')
		return (CUB_EA);
	else if (line[0] == 'S' && line[1] == ' ')
		return (CUB_S);
	else if (line[0] == 'F' && line[1] == ' ')
		return (CUB_F);
	else if (line[0] == 'C' && line[1] == ' ')
		return (CUB_C);
	return (CUB_MAP);
}

int			parse_line(t_config *config, char const *line, t_str **map_buffer)
{
	static int	empty_in_map = 0;
	static int	content_after = 0;
	int			len;
	int			key;

	len = ft_strlen((char*)line);
	if (len == 0 && config->set[CUB_MAP])
		empty_in_map = 1;
	if (empty_in_map && content_after)
		return (0);
	if (len == 0)
		return (1);
	key = config_key(line);
	if (key != CUB_MAP && (config->set[key] || config->set[CUB_MAP]))
		return (0);
	if (key == CUB_R)
		return (parse_dimensions(config, line));
	else if (key >= CUB_NO && key <= CUB_S)
		return (parse_textures(config, key, line));
	else if (key == CUB_F || key == CUB_C)
		return (parse_color(config, key, line));
	config->set[key] = 1;
	if (empty_in_map)
		content_after = 1;
	return (!!t_str_add_back(map_buffer, ft_strdup(line)));
}

int			parse_config(t_config *config, t_camera *camera, char *file_path)
{
	int		cub_fd;
	char	*line;
	int		read;

	if ((cub_fd = open(file_path, O_RDONLY)) < 0)
	{
		printf("Error\nCub3D: %s: %s", file_path, NO_FILE);
		return (0);
	}
	config->map_buffer = NULL;
	read = 1;
	while (get_next_line(cub_fd, &line))
	{
		read = (read && parse_line(config, line, &config->map_buffer));
		free(line);
	}
	if (read && ft_strlen(line) > 0)
		read = !!t_str_add_back(&config->map_buffer, ft_strdup(line));
	free(line);
	close(cub_fd);
	if (!read || !parse_map(config, config->map_buffer, camera))
		return (t_str_clear(&config->map_buffer));
	return (1);
}
