/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:03:04 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/02/10 12:49:35 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../utils/utils.h"

# define BUFFER_SIZE 128

int		get_next_line(int fd, char **line);

char	*ft_strjoin(char *s1, char *s2);
int		find_endl(char *s);

int		ft_strlen(const char *s);
void	*ft_memmove(void *dst, void *src, unsigned long len);

#endif
