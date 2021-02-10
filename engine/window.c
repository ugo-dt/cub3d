/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:09:56 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/02/09 11:53:04 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int		init_image(t_window *window, t_image *img)
{
	if (!(img->img = mlx_new_image(
					window->mlx_ptr, window->size.x, window->size.y)))
		return (0);
	img->addr = mlx_get_data_addr(
					img->img, &img->bpp, &img->size_line, &img->endian);
	return (1);
}

int		init_window(t_window *window, t_config *config)
{
	set_pos(&window->size, config->usr_width, config->usr_height);
	if (window->size.x > 1920)
		window->size.x = 1920;
	if (window->size.y > 1080)
		window->size.y = 1080;
	if (window->size.x < 100)
		window->size.x = 100;
	if (window->size.y < 100)
		window->size.y = 100;
	window->mlx_ptr = NULL;
	window->window = NULL;
	if (!(window->mlx_ptr = mlx_init()) ||
		!(window->window = mlx_new_window(
			window->mlx_ptr, window->size.x, window->size.y, "Cub3D")))
		return (0);
	set_pos(&window->half, window->size.x / 2, window->size.y / 2);
	if (!init_image(window, &window->screen))
		return (0);
	return (1);
}

void	clear_window(t_window *window)
{
	if (window->screen.img)
		mlx_destroy_image(window->mlx_ptr, window->screen.img);
	if (window->mlx_ptr && window->window)
		mlx_destroy_window(window->mlx_ptr, window->window);
}

void	update_window(t_game *game)
{
	t_window	*w;

	w = &game->window;
	mlx_put_image_to_window(w->mlx_ptr, w->window, w->screen.img, 0, 0);
}
