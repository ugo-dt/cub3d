/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:37:52 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/02/14 12:43:29 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

static int		file_type(int fd, int filesize, t_game *game)
{
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	tmp = game->window.size.x;
	set_int_in_char(bmpfileheader + 18, tmp);
	tmp = game->window.size.y;
	set_int_in_char(bmpfileheader + 22, tmp);
	bmpfileheader[27] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

static int		get_color(t_window *w, int x, int y)
{
	int	rgb;
	int	color;

	color = *(int*)(w->screen.addr
			+ (4 * (int)w->size.x * ((int)w->size.y - 1 - y))
			+ (4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

static int		write_bmp_data(int file, t_window *w, int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					color;

	i = 0;
	while (i < (int)w->size.y)
	{
		j = 0;
		while (j < (int)w->size.x)
		{
			color = get_color(w, j, i);
			if (write(file, &color, 3) < 0)
				return (0);
			if (pad > 0 && write(file, &zero, pad) < 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int				save_frame(t_game *game)
{
	int			fd;
	t_window	*w;
	int			filesize;
	int			pad;

	w = &game->window;
	pad = (4 - ((int)w->size.x * 3) % 4) % 4;
	filesize = 54 + (3 * ((int)w->size.x + pad) * (int)w->size.y);
	if ((fd = open("screenshot.bmp", O_RDWR | O_CREAT | O_TRUNC | O_APPEND,
								S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		return (0);
	if (!(file_type(fd, filesize, game)))
		return (0);
	if (!write_bmp_data(fd, w, pad))
		return (0);
	close(fd);
	return (1);
}
