/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 19:13:44 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/02 04:27:07 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		g_strlen(char *s)
{
	int size = 0;

	while (s[size])
		size++;
	return (size);
}

char			*g_strjoin(char *s1, char *s2)
{
	char	*s;
	int		i;
	
	if (!(s = (char *)malloc(sizeof(char *) * (g_strlen(s1) + g_strlen(s2) + 1))))
		error();
	i = 0;	
	while (*s1)	
		s[i++] = *s1++;
	while (*s2)
		s[i++] = *s2++;
	s[i] = 0;
	return (s);
}

int				get_next_line(int fd, char **line)
{
	char	buf[2];
	char	*s;
	char	*temp;
	int 	i, ret;

	i = 0;
	while (i < 2)
		buf[i++] = 0;
	s = g_strjoin("", "");
	while ((ret = read(fd, buf, 1)) > 0)
	{
		if (buf[0] == '\n')
			break ;
		temp = g_strjoin(s, buf);
		free_one(s);
		s = temp;
	}
	*line = s;
	return (ret);
}
