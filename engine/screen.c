/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:32:03 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/02/14 12:32:27 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	update_screen(t_game *game)
{
	t_pos	start;
	int		i;
	t_ray	ray;

	set_pos(&start, 0, 0);
	draw_rectangle(&game->window, &start, &game->window.size, 0x0);
	i = 0;
	while (i < game->window.size.x)
	{
		ray_cast(game, &ray, i);
		game->depth[i] = ray.distance;
		ray.height = fabs(game->window.size.y / ray.distance);
		draw_wall(game, &ray);
		if (ray.height < game->window.size.y)
			draw_sky_floor(game, &ray);
		i++;
	}
	if (game->sprites)
		draw_sprites(game);
	if (game->ui)
		update_ui(game);
}
