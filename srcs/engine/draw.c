/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:06:35 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/02/03 11:56:15 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	restrain_pos(t_pos *pos, t_pos *win_size)
{
	if (pos->x < 0)
		pos->x = 0;
	if (pos->x > win_size->x)
		pos->x = win_size->x - 1;
	if (pos->y < 0)
		pos->y = 0;
	if (pos->y > win_size->y)
		pos->y = win_size->y - 1;
}

void	draw_pixel(t_window *w, t_pos *pos, int color)
{
	if (pos->x >= 0 && pos->x < w->size.x && pos->y >= 0 && pos->y < w->size.y)
	{
		*(int*)(w->screen.addr +
		(4 * (int)w->size.x * (int)pos->y) +
		((int)pos->x * 4)) = color;
	}
}

void	draw_line(t_window *window, t_pos *p1, t_pos *p2, int color)
{
	t_pos	p1_temp;
	t_pos	p2_temp;
	double	step;
	double	i;

	p2_temp.x = p2->x - p1->x;
	p2_temp.y = p2->y - p1->y;
	if (fabs(p2_temp.x) >= fabs(p2_temp.y))
		step = fabs(p2_temp.x);
	else
		step = fabs(p2_temp.y);
	p2_temp.x = p2_temp.x / step;
	p2_temp.y = p2_temp.y / step;
	p1_temp.x = p1->x;
	p1_temp.y = p1->y;
	i = 0;
	while (i <= step)
	{
		draw_pixel(window, &p1_temp, color);
		p1_temp.x += p2_temp.x;
		p1_temp.y += p2_temp.y;
		i++;
	}
}

int		draw_vertical_line(t_window *win, t_pos *start, int length, int color)
{
	int		i;
	int		j;
	t_pos	pos;
	int		limit;

	restrain_pos(start, &win->size);
	pos.x = start->x;
	limit = (int)win->size.y;
	i = 0;
	while (i < length && (j = start->y + i) < limit)
	{
		pos.y = j;
		draw_pixel(win, &pos, color);
		i++;
	}
	return (1);
}

int		draw_rectangle(t_window *window, t_pos *p1, t_pos *p2, int color)
{
	int		i;
	int		j;
	t_pos	pos;

	restrain_pos(p1, &window->size);
	restrain_pos(p2, &window->size);
	i = p1->y;
	while (i < p2->y)
	{
		pos.y = i;
		j = p1->x;
		while (j < p2->x)
		{
			pos.x = j++;
			draw_pixel(window, &pos, color);
		}
		i++;
	}
	return (1);
}
