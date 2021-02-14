/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:35:03 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/01/20 11:35:05 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int		move_camera_y(t_game *game, int direction)
{
	t_camera	*c;
	t_pos		new_pos;

	c = &game->camera;
	copy_pos(&new_pos, &c->pos);
	new_pos.x += (((direction) ? -1 : 1) * (c->dir.x * .11));
	if (in_map(&new_pos, &game->config)
		&& get_value_in_map(&new_pos, &game->config) != '1'
		&& get_value_in_map(&new_pos, &game->config) != '2')
		copy_pos(&c->pos, &new_pos);
	copy_pos(&new_pos, &c->pos);
	new_pos.y += (((direction) ? -1 : 1) * (c->dir.y * .11));
	if (in_map(&new_pos, &game->config)
		&& get_value_in_map(&new_pos, &game->config) != '1'
		&& get_value_in_map(&new_pos, &game->config) != '2')
		copy_pos(&c->pos, &new_pos);
	return (1);
}

int		move_camera_x(t_game *game, int direction)
{
	t_camera	*c;
	t_pos		new_pos;

	c = &game->camera;
	copy_pos(&new_pos, &c->pos);
	new_pos.x += (((direction) ? -1 : 1) * (c->x_dir.x * .11) + 0.00001);
	if (in_map(&new_pos, &game->config)
		&& get_value_in_map(&new_pos, &game->config) != '1'
		&& get_value_in_map(&new_pos, &game->config) != '2')
		copy_pos(&c->pos, &new_pos);
	copy_pos(&new_pos, &c->pos);
	new_pos.y += (((direction) ? -1 : 1) * (c->x_dir.y * .11) + 0.00001);
	if (in_map(&new_pos, &game->config)
		&& get_value_in_map(&new_pos, &game->config) != '1'
		&& get_value_in_map(&new_pos, &game->config) != '2')
		copy_pos(&c->pos, &new_pos);
	return (1);
}

int		rotate_camera(t_game *game, int dir)
{
	t_camera	*c;
	t_pos		old;

	c = &game->camera;
	copy_pos(&old, &c->dir);
	c->dir.x = (c->dir.x * game->cos[dir]) - (c->dir.y * game->sin[dir]);
	c->dir.y = (old.x * game->sin[dir]) + (c->dir.y * game->cos[dir]);
	copy_pos(&old, &c->plane);
	c->plane.x = (c->plane.x * game->cos[dir]) - (c->plane.y * game->sin[dir]);
	c->plane.y = (old.x * game->sin[dir]) + (c->plane.y * game->cos[dir]);
	copy_pos(&old, &c->x_dir);
	c->x_dir.x = (c->x_dir.x * game->cos[dir]) - (c->x_dir.y * game->sin[dir]);
	c->x_dir.y = (old.x * game->sin[dir]) + (c->x_dir.y * game->cos[dir]);
	return (1);
}
