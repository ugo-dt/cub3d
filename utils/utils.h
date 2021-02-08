/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:11:46 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/01/12 15:54:47 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdio.h>

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

int				ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
char			*ft_strnstr(char *big, char *little, unsigned int len);
char			*ft_strdup(const char *s);
int				char_in_str(char c, char *s);
char			*ft_substr(const char *s, unsigned int start, unsigned int len);
void			*ft_memmove(void *dst, void *src, unsigned long len);
int				ft_atoi(const char *nptr);

t_str			*t_str_add_back(t_str **str, char *content);
t_str			*t_str_last(t_str *str);
t_str			*t_str_split(const char *str, const char sep);
int				t_str_size(t_str *str);
int				t_str_clear(t_str **list);

#endif

/*
**  UTILS_H
*/
