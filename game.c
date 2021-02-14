/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:25:52 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/02/14 12:36:35 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_sprites(t_game *game)
{
	int			i;
	int			j;
	char		c;
	t_pos		pos;
	t_texture	*texture;

	game->sprites = NULL;
	i = 0;
	while (i < game->config.rows)
	{
		j = 0;
		while (j < game->config.columns)
		{
			set_pos(&pos, j + .5, i + .5);
			c = get_value_in_map(&pos, &game->config);
			texture = &game->textures[TEX_SPRITE + (c - '0' - 2)];
			if (c >= '2' && c <= '4' && texture->tex
				&& !add_front_sprite(&game->sprites, 0., &pos, texture))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int			exit_game(t_game *game, int status)
{
	clear_config(&game->config);
	clear_window(&game->window);
	clear_textures(game);
	clear_sprites(&game->sprites);
	exit(status);
	return (status);
}

void		init_game(t_game *game)
{
	init_config(&game->config);
	game->shadows = 1;
	game->ui = 0;
	game->sprites = NULL;
}

int			game_launch(t_game *game)
{
	if (!(init_window(&game->window, &game->config)))
		exit_error(game, "Error\nCub3D: could not create window or image\n");
	if (!load_textures(game))
		return (exit_error(game, "Error\nCub3D: could not load textures\n"));
	if (!find_sprites(game))
		return (exit_error(game, "Error:\nfailed to malloc sprites.\n"));
	calculate(game);
	return (1);
}

int			screenshot(t_game *game)
{
	update_screen(game);
	update_ui(game);
	update_window(game);
	if (!save_frame(game))
		exit_error(game, "Error\nCub3D: could not save screenshot\n");
	return (exit_game(game, EXIT_SUCCESS));
}
