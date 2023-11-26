/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:37:43 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/02/10 14:58:58 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define KEY_W			0x0077
#define KEY_A			0x0061
#define KEY_S			0x0073
#define KEY_D			0x0064
#define KEY_M			0x006d
#define KEY_ESC			0xff1b
#define KEY_LEFT		0xff51
#define KEY_RIGHT		0xff53

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
