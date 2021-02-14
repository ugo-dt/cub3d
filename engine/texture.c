/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:34:58 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/01/22 12:15:31 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int	load_tex(t_window *window, t_texture *tex, char *path)
{
	if (path)
	{
		tex->path = path;
		if ((tex->tex = mlx_xpm_file_to_image(window->mlx_ptr,
			path, &tex->width, &tex->height)))
			tex->addr = mlx_get_data_addr(tex->tex,
				&tex->bpp, &tex->size_line, &tex->endian);
		else
			return (0);
	}
	return (1);
}

void		clear_textures(t_game *g)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
	{
		if (g->textures[i].tex)
			mlx_destroy_image(g->window.mlx_ptr, g->textures[i].tex);
		g->textures[i].tex = NULL;
		g->textures[i].addr = NULL;
		i++;
	}
}

static int	line_is_empty(t_texture *tex, int line)
{
	int		i;
	t_pos	pos;

	pos.y = line;
	i = 0;
	while (i < tex->width)
	{
		pos.x = i;
		if (get_tex_color(tex, &pos) != 0x0)
			return (0);
		i++;
	}
	return (1);
}

static int	col_is_empty(t_texture *tex, int column)
{
	int		i;
	t_pos	pos;

	pos.x = column;
	i = 0;
	while (i < tex->height)
	{
		pos.y = i;
		if (get_tex_color(tex, &pos) != 0x0)
			return (0);
		i++;
	}
	return (1);
}

int			load_textures(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < TEXTURES)
	{
		if (!load_tex(&g->window, &g->textures[i], g->config.tex_path[i]))
			return (0);
		j = 0;
		while (j < g->textures[i].height && col_is_empty(&g->textures[i], j))
			j++;
		g->textures[i].start.x = j;
		while (j < g->textures[i].height && !col_is_empty(&g->textures[i], j))
			j++;
		g->textures[i].end.x = j;
		j = 0;
		while (j < g->textures[i].height && line_is_empty(&g->textures[i], j))
			j++;
		g->textures[i].start.y = j;
		while (j < g->textures[i].height && !line_is_empty(&g->textures[i], j))
			j++;
		g->textures[i].end.y = j;
		i++;
	}
	return (1);
}
