/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 23:21:15 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/26 15:41:56 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void	player_pos_angle(
	t_config *config, char dir, t_pos *pos, t_camera *camera)
{
	camera->pos.x = pos->x + 0.5 - 1;
	camera->pos.y = pos->y + 0.5 - 1;
	if (dir == 'N')
	{
		set_pos(&camera->dir, 0., -1.);
		set_pos(&camera->plane, config->fov, 0);
	}
	else if (dir == 'E')
	{
		set_pos(&camera->dir, 1., 0.);
		set_pos(&camera->plane, 0., config->fov);
	}
	else if (dir == 'S')
	{
		set_pos(&camera->dir, 0., 1.);
		set_pos(&camera->plane, -config->fov, 0.);
	}
	else if (dir == 'W')
	{
		set_pos(&camera->dir, -1., 0.);
		set_pos(&camera->plane, 0., -config->fov);
	}
	set_pos(&camera->x_dir, camera->dir.y, -camera->dir.x);
	dir = '0';
}

int		copy_map(t_config *config, t_str *map_buffer, int *map, int dir)
{
	int		i;
	int		j;
	int		line;

	i = 0;
	while (map_buffer)
	{
		j = 0;
		line = 0;
		while (map_buffer->content[j] == ' ' && map_buffer->content[j])
			j++;
		while (map_buffer->content[j])
		{
			map[(i * config->columns) + line++] = map_buffer->content[j];
			if (ft_strchr(DIRECTIONS, map_buffer->content[j]))
			{
				map_buffer->content[j] = '0';
				dir++;
			}
			j++;
		}
		map_buffer = map_buffer->next;
		i++;
	}
	return (dir);
}

void	init_map(t_config *config, t_str *map_buffer)
{
	int		rows;
	int		columns;

	rows = 0;
	config->columns = 0;
	while (map_buffer)
	{
		columns = ft_strlen(map_buffer->content);
		if (config->columns < columns)
			config->columns = columns;
		rows++;
		map_buffer = map_buffer->next;
	}
	config->rows = rows;
}

int		parse_map(t_config *config, t_str *map_buffer, t_camera *camera)
{
	int		*map;

	init_map(config, map_buffer);
	map = NULL;
	if (config->columns <= 2 || config->rows <= 2 ||
		!check_valid(config, map_buffer, camera))
		return (0);
	if (!(map = (int*)malloc(sizeof(*map) * config->columns * config->rows)))
		return (0);
	if (copy_map(config, map_buffer, map, 0) != 1)
		return (0);
	config->map = map;
	config->map_size = config->columns * config->rows;
	return (1);
}
