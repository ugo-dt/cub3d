/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:03:04 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/26 16:02:36 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <libft.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 128

int		get_next_line(int fd, char **line);
int		find_endl(char *s);
char	*gnl_join(char *s1, char *s2);
void	*gnl_move(void *dst, void *src, unsigned long len);

#endif
