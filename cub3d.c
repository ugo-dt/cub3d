/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:37:43 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/01/22 15:17:12 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define KEY_W		6
#define KEY_A		12
#define KEY_S		1
#define KEY_D		2
#define KEY_M		41
#define KEY_ESC		53
#define KEY_LEFT	123
#define KEY_RIGHT	124

int		exit_hook(t_game *game)
{
	return (exit_game(game, EXIT_SUCCESS));
}

int		key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.key_w = 1;
	if (keycode == KEY_A)
		game->keys.key_a = 1;
	if (keycode == KEY_S)
		game->keys.key_s = 1;
	if (keycode == KEY_D)
		game->keys.key_d = 1;
	if (keycode == KEY_LEFT)
		game->keys.key_left = 1;
	if (keycode == KEY_RIGHT)
		game->keys.key_right = 1;
	if (keycode == KEY_ESC)
		exit_game(game, EXIT_SUCCESS);
	game->config.options.update = 1;
	return (0);
}

int		key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.key_w = 0;
	if (keycode == KEY_A)
		game->keys.key_a = 0;
	if (keycode == KEY_S)
		game->keys.key_s = 0;
	if (keycode == KEY_D)
		game->keys.key_d = 0;
	if (keycode == KEY_LEFT)
		game->keys.key_left = 0;
	if (keycode == KEY_RIGHT)
		game->keys.key_right = 0;
	if (keycode == KEY_M)
		game->ui = (game->ui == 1 ? 0 : 1);
	game->config.options.update = 1;
	return (0);
}

int		main_loop(t_game *game)
{
	if (game->keys.key_w)
		game->config.options.update = move_camera_y(game, 0);
	if (game->keys.key_s)
		game->config.options.update = move_camera_y(game, 1);
	if (game->keys.key_a)
		game->config.options.update = move_camera_x(game, 0);
	if (game->keys.key_d)
		game->config.options.update = move_camera_x(game, 1);
	if (game->keys.key_left)
		game->config.options.update = rotate_camera(game, 0);
	if (game->keys.key_right)
		game->config.options.update = rotate_camera(game, 1);
	if (game->config.options.update)
	{
		update_screen(game);
		update_window(game);
		game->config.options.update = 0;
	}
	return (0);
}
