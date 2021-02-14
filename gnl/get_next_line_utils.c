/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:43:17 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/01/11 15:14:56 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		find_endl(char *s)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		if (s[i++] == '\n')
			return (1);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	int		len;
	char	*rtn;

	if (!s1 && !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	len = s1_len + s2_len;
	if (!(rtn = malloc(sizeof(char) * len + 1)))
		return (NULL);
	ft_memmove(rtn, s1, s1_len);
	ft_memmove(rtn + s1_len, s2, s2_len);
	rtn[len] = '\0';
	free((char *)s1);
	return (rtn);
}
