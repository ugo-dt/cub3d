/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:24:00 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/26 15:42:41 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "engine.h"
# include "utils.h"
# include "config.h"
# include "X11/X.h"
# include "sys/stat.h"

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
