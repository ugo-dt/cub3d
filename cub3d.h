/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:24:00 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/02/14 12:43:13 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "engine/engine.h"
# include "utils/utils.h"
# include "config/config.h"
# include "X11/X.h"
# include "sys/stat.h"

int				ft_strlen(const char *s);

int				exit_game(t_game *game, int status);

int				exit_hook(t_game *game);

int				key_press(int keycode, t_game *game);

int				key_release(int keycode, t_game *game);

int				main_loop(t_game *game);

int				exit_error(t_game *game, char *s);

void			init_game(t_game *game);

int				screenshot(t_game *game);

int				game_launch(t_game *game);

int				save_frame(t_game *game);

#endif

/*
**	CUB3D_H
*/
