/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:11:46 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/26 15:49:19 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include <libft.h>

typedef struct	s_str
{
	char			*content;
	struct s_str	*next;
}				t_str;

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_pos;

void			set_pos(t_pos *pos, double x, double y);
void			copy_pos(t_pos *pos_to, t_pos *pos_from);

t_str			*t_str_add_back(t_str **str, char *content);
t_str			*t_str_last(t_str *str);
t_str			*t_str_split(const char *str, const char sep);
int				t_str_size(t_str *str);
int				t_str_clear(t_str **list);

#endif

/*
**  UTILS_H
*/
