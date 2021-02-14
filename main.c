/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:24:12 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/02/10 12:55:25 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exit_error(t_game *game, char *s)
{
	if (s)
		write(STDERR_FILENO, s, ft_strlen(s));
	exit_game(game, EXIT_FAILURE);
	return (EXIT_FAILURE);
}

int		check_arguments(t_game *game, int argc, char **argv)
{
	char	*s;

	if (argc < 2)
		exit_error(game, "Error\nCub3D: expected more arguments\n");
	else if (argc > 3)
		exit_error(game, "Error\nCub3D: expected less arguments\n");
	else
	{
		s = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
		if (!s || ft_strncmp(s, ".cub", 5) != 0)
			exit_error(game, "Error\nCub3D: expected.cub file\n");
		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save", 7) == 0)
				return (1);
			else
			{
				write(1, "Error\nCub3D: invalid option: ", 29);
				exit_error(game, argv[2]);
			}
		}
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_game		game;

	init_game(&game);
	game.config.options.screenshot = check_arguments(&game, argc, argv);
	if (!(parse_config(&game.config, &game.camera, argv[1])))
		exit_error(&game, "Error\nCub3D: invalid map\n");
	if (!game_launch(&game))
		return (1);
	if (game.config.options.screenshot)
		return (screenshot(&game));
	mlx_hook(game.window.window, KeyPress, (1L << 0), &key_press, &game);
	mlx_hook(game.window.window, KeyRelease, (1L << 1), &key_release, &game);
	mlx_hook(game.window.window, ClientMessage, (1L << 17), &exit_hook, &game);
	mlx_loop_hook(game.window.mlx_ptr, &main_loop, &game);
	mlx_loop(game.window.mlx_ptr);
	return (0);
}
