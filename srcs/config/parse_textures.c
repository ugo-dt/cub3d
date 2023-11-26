/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:23:11 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/02/14 12:50:26 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

static char	*path_from_line(int start, char const *line)
{
	int		start_def;
	int		end;
	char	*path;

	start_def = start;
	if (!line)
		return (NULL);
	while (line[start] && line[start] == ' ')
		start++;
	end = ft_strlen(line);
	while (line[end] == ' ')
		end--;
	if (start == start_def || end - start <= 0
		|| !(path = ft_substr(line, start, end - start)))
		return (NULL);
	return (path);
}

static int	texture_index(int key)
{
	if (key == CUB_NO)
		return (TEX_NORTH);
	else if (key == CUB_SO)
		return (TEX_SOUTH);
	else if (key == CUB_WE)
		return (TEX_WEST);
	else if (key == CUB_EA)
		return (TEX_EAST);
	return (TEX_SPRITE);
}

int			free_textures(t_config *config)
{
	int		index;

	index = 0;
	while (index < TEXTURES)
	{
		if (config->tex_path[index])
			free(config->tex_path[index]);
		config->tex_path[index] = NULL;
		index++;
	}
	return (0);
}

int			parse_textures(t_config *config, int key, char const *line)
{
	char	*path;
	int		index;

	index = texture_index(key);
	if (config->tex_path[index])
	{
		free(config->tex_path[index]);
		config->tex_path[index] = NULL;
	}
	if (!(path = path_from_line((index == TEX_SPRITE) ? 1 : 2, line)))
		return (free_textures(config));
	config->tex_path[index] = path;
	return (1);
}
