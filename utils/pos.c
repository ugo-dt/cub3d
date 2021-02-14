/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:26:30 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/01/08 15:33:24 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	set_pos(t_pos *pos, double x, double y)
{
	pos->x = x;
	pos->y = y;
}

void	copy_pos(t_pos *pos_to, t_pos *pos_from)
{
	pos_to->x = pos_from->x;
	pos_to->y = pos_from->y;
}
