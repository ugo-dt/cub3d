/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:24:10 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/02/14 12:32:54 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int
	case_color(t_game *game, int x, int y)
{
	char	c;
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	c = get_value_minimap(&pos, &game->config);
	if (c == '1')
		return (BLACK);
	else if (c >= '2' && c <= '4')
		return (0xababab);
	else if (--y == (int)game->camera.pos.y
			&& --x == (int)game->camera.pos.x)
		return (GREEN);
	return (WHITE);
}

static void
	draw_minimap(t_game *game, t_window *w, t_pos *start, t_pos *end)
{
	int			i;
	int			j;
	int			color;

	i = 0;
	while (i < game->config.rows)
	{
		j = 0;
		while (j < game->config.columns)
		{
			if ((color = case_color(game, j, i)) >= 0)
			{
				set_pos(start,
					w->size.x - (game->config.columns * 5) - 5 + (j * 5),
					w->size.y - (game->config.rows * 5) - 5 + (i * 5));
				set_pos(end,
					w->size.x - (game->config.columns * 5) + (j * 5),
					w->size.y - (game->config.rows * 5) + (i * 5));
				draw_rectangle(w, start, end, color);
			}
			j++;
		}
		i++;
	}
}

void
	update_ui(t_game *game)
{
	t_window	*w;
	t_pos		start;
	t_pos		end;

	w = &game->window;
	if (game->config.options.screenshot == 0)
		draw_minimap(game, w, &start, &end);
}
