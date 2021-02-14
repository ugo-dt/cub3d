/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sky_floor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 18:04:04 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/01/20 11:35:40 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	draw_floor(t_game *game, t_ray *ray, t_pos *pixel)
{
	draw_pixel(&game->window, pixel, distance_shade(game->shadows,
				game->config.color[TEX_FLOOR], game->sf_dist[ray->row]));
}

void	draw_sky(t_game *game, t_pos *pixel)
{
	draw_pixel(&game->window, pixel, game->config.color[TEX_SKY]);
}

void	draw_sky_floor(t_game *game, t_ray *ray)
{
	int		i;
	t_pos	pixel;
	double	weight;

	pixel.x = ray->column;
	i = game->window.half.y + (ray->height / 2.);
	while (i < game->window.size.y)
	{
		ray->row = (int)i;
		weight = game->sf_dist[i] / ray->distance;
		set_pos(&ray->c_floor,
			weight * ray->floor_wall.x + (1. - weight) * game->camera.pos.x,
			weight * ray->floor_wall.y + (1. - weight) * game->camera.pos.y);
		pixel.y = i;
		draw_floor(game, ray, &pixel);
		pixel.y = game->window.size.y - i++;
		draw_sky(game, &pixel);
	}
}
