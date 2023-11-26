/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 18:48:01 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/01/20 11:21:36 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void		calculate_camera_x(double width, double *r)
{
	int	i;

	i = 0;
	while (i < width)
	{
		r[i] = ((2. * (double)i) / width) - 1.;
		i++;
	}
}

static void		calculate_cos_sin(double r_speed, double *cos_r, double *sin_r)
{
	cos_r[0] = cos(-r_speed);
	cos_r[1] = cos(r_speed);
	sin_r[0] = sin(-r_speed);
	sin_r[1] = sin(r_speed);
}

static void		calculate_sf_dist(double height, double *r)
{
	int	i;

	i = 0;
	while (i < height)
	{
		r[i] = (height / (2. * (double)i - height));
		i++;
	}
}

void			calculate(t_game *game)
{
	calculate_camera_x(game->window.size.x, game->camera_x);
	calculate_cos_sin(game->config.rotate_speed, game->cos, game->sin);
	calculate_sf_dist(game->window.size.y, game->sf_dist);
}
