/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:30:45 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/26 15:42:03 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

int			parse_dimensions(t_config *config, char const *line)
{
	int		i;
	int		temp;
	t_str	*str;
	t_str	*param;

	i = 0;
	while (line[++i])
		if (line[i] != ' ' && !(line[i] >= '0' && line[i] <= '9'))
			return (0);
	str = NULL;
	if (!(str = t_str_split(line, ' ')) || t_str_size(str) != 3)
		return (t_str_clear(&str));
	param = str->next;
	temp = ft_atoi(param->content);
	if (temp <= 1)
		return (t_str_clear(&str));
	config->usr_width = temp;
	param = param->next;
	temp = ft_atoi(param->content);
	if (temp <= 1)
		return (t_str_clear(&str));
	config->usr_height = temp;
	return (t_str_clear(&str) | 1);
}

static int	str_to_color(t_str *str)
{
	int	i;
	int	color;
	int	tmp;

	i = 0;
	color = 0;
	while (str)
	{
		tmp = ft_atoi(str->content);
		if (tmp < 0 || tmp > 255)
			return (-1);
		color = color | (tmp << (16 - (i++ * 8)));
		str = str->next;
	}
	return (color);
}

int			parse_color(t_config *config, int key, char const *line)
{
	int				i;
	unsigned int	color;
	t_str			*str[2];

	i = 1;
	while (line[i])
		if (!ft_strchr("0123456789, ", line[i++]))
			return (0);
	str[0] = NULL;
	str[1] = NULL;
	if (!(str[0] = t_str_split(line, ' ')) || t_str_size(str[0]) != 2
		|| !(str[1] = t_str_split(str[0]->next->content, ','))
		|| t_str_size(str[1]) != 3)
		return (t_str_clear(&str[0]) || t_str_clear(&str[1]));
	if ((int)((color = str_to_color(str[1]))) < 0)
		return (t_str_clear(&str[0]) || t_str_clear(&str[1]));
	config->color[(key == CUB_F) ? TEX_FLOOR : TEX_SKY] = color;
	return ((t_str_clear(&str[0]) || t_str_clear(&str[1])) | 1);
}
