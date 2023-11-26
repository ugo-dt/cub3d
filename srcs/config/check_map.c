/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:42:33 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/26 15:43:07 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

int		hole_2(t_str *map_buffer, int i, int j)
{
	t_str	*begin;
	int		temp_i;

	begin = map_buffer;
	temp_i = i;
	while (i-- >= 0)
		map_buffer = map_buffer->next;
	if (!ft_strchr("012348NSEW", map_buffer->content[j]) || !ft_strchr(
		"012348NSEW", map_buffer->content[j - 1]) || !ft_strchr(
		"012348NSEW", map_buffer->content[j + 1]))
		return (1);
	map_buffer = begin;
	i = temp_i;
	while (--i > 0)
		map_buffer = map_buffer->next;
	if (!ft_strchr("012348NSEW", map_buffer->content[j]) || !ft_strchr(
		"012348NSEW", map_buffer->content[j - 1]) || !ft_strchr(
		"012348NSEW", map_buffer->content[j + 1]))
		return (1);
	return (0);
}

int		hole(t_config *config, t_str *map_buffer, int i, int j)
{
	t_str	*begin;
	int		temp_i;

	begin = map_buffer;
	temp_i = i;
	if (i == 0 || j == 0 || i == config->rows - 1 || j == config->columns - 1)
		return (1);
	while (i-- > 0)
		map_buffer = map_buffer->next;
	if (!ft_strchr("012348NSEW", map_buffer->content[j - 1])
		|| !ft_strchr("012348NSEW", map_buffer->content[j + 1]))
		return (1);
	map_buffer = begin;
	i = temp_i;
	return (hole_2(map_buffer, i, j));
}

int		check_holes(t_config *config, t_str *map_buffer)
{
	int		i;
	int		j;
	t_str	*begin;

	i = 0;
	begin = map_buffer;
	while (map_buffer)
	{
		j = 0;
		while (j < config->columns && map_buffer->content[j])
		{
			if (ft_strchr("02NSEW", map_buffer->content[j]) &&
				hole(config, begin, i, j))
				return (0);
			j++;
		}
		map_buffer = map_buffer->next;
		i++;
	}
	return (1);
}

int		check_valid(t_config *config, t_str *map_buffer, t_camera *camera)
{
	t_pos	pos;

	pos.y = 0;
	if (!check_holes(config, map_buffer))
		return (0);
	while (map_buffer)
	{
		pos.x = 0;
		while (map_buffer->content[(int)pos.x])
		{
			if (!ft_strchr(
					VALID_MAP_CHARACTERS, map_buffer->content[(int)pos.x]))
				return (0);
			if (ft_strchr(DIRECTIONS, map_buffer->content[(int)pos.x]))
				player_pos_angle(
					config, map_buffer->content[(int)pos.x], &pos, camera);
			pos.x++;
		}
		map_buffer = map_buffer->next;
		pos.y++;
	}
	return (1);
}
