/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:57:56 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/26 15:48:19 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

char	map_xy(int x, int y, t_config *config)
{
	return (config->map[y * config->columns + x]);
}

int		in_map(t_pos *p, t_config *config)
{
	int		i;
	int		j;
	t_str	*map_buffer;

	if (!config->map_buffer)
		return (0);
	map_buffer = config->map_buffer;
	i = 0;
	while (map_buffer && i++ < p->y)
		map_buffer = map_buffer->next;
	if (!map_buffer)
		return (0);
	j = 0;
	while (map_buffer->content[j] && j < p->x)
		j++;
	if (j < (int)ft_strlen(map_buffer->content))
		return (1);
	return (p->x >= 0 && p->y >= 0 && p->x < config->columns &&
			p->y < config->rows && i >= 0 && j >= 0 && i < config->rows &&
			j < config->columns);
}

char	get_value_minimap(t_pos *p, t_config *config)
{
	int		i;
	t_str	*map_buffer;

	if (!config->map_buffer)
		return ('1');
	i = 0;
	map_buffer = config->map_buffer;
	while (map_buffer && i++ < p->y)
		map_buffer = map_buffer->next;
	if (!map_buffer)
		return ('0');
	if (p->x > ft_strlen(map_buffer->content))
		return ('0');
	return (map_buffer->content[(int)p->x]);
}

char	get_value_in_map(t_pos *p, t_config *config)
{
	int		i;
	int		j;
	t_str	*map_buffer;

	if (!config->map_buffer)
		return ('1');
	map_buffer = config->map_buffer;
	i = 0;
	while (map_buffer && i++ <= p->y)
		map_buffer = map_buffer->next;
	if (!map_buffer || !map_buffer->content)
		return ('1');
	j = 0;
	while (map_buffer->content[j] && j <= p->x)
		j++;
	if (j >= 0 && j < (int)ft_strlen(map_buffer->content))
		return (map_buffer->content[j]);
	if ((int)(p->y * config->columns + (int)p->x) < config->map_size)
		return (config->map[(int)p->y * config->columns + (int)p->x]);
	return ('1');
}
