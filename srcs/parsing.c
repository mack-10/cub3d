/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 16:27:01 by sujeon            #+#    #+#             */
/*   Updated: 2021/04/25 21:55:21 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_val(char **s, int n)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (n != i)
		return (0);
	if (n == 3)
	{
		if (!s[1] || !s[2])
			return (0);
	}
	else
	{
		if (!s[1])
			return (0);
	}
	return (1);
}

static void	tex_path(t_val *lst, char **src)
{
	if (src[0][0] == 'N' && src[0][1] == 'O')
		lst->tex_path[0] = src[1];
	else if (src[0][0] == 'S' && src[0][1] == 'O')
		lst->tex_path[1] = src[1];
	else if (src[0][0] == 'W' && src[0][1] == 'E')
		lst->tex_path[2] = src[1];
	else if (src[0][0] == 'E' && src[0][1] == 'A')
		lst->tex_path[3] = src[1];
	else if (src[0][0] == 'S')
		lst->s_path = src[1];
	else
		error();
}

static void	get_value(t_val *lst, char *s)
{
	char	**src;

	src = ft_split(s, ' ');
	if (s[0] == 'R' && check_val(src, 3))
	{
		lst->screenW = ft_atoi(src[1]);
		lst->screenH = ft_atoi(src[2]);
	}
	else if (s[0] == 'F' && check_val(src, 2))
		lst->par.f_rgb = src[1];
	else if (s[0] == 'C' && check_val(src, 2))
		lst->par.c_rgb = src[1];
	else
	{
		if (check_val(src, 2))
			tex_path(lst, src);
		else
			error();
	}
	free(src);
}

static void	map_set_value(t_val *lst, char *src)
{
	if (src[0] == '0' || src[0] == '1')
	{
		//printf("map |%s\n", src);
	}
	else if (src[0])
	{
		get_value(lst, src);
		lst->par.cnt_set++;
	}
}

int			 parsing(t_val *lst, int fd)
{
	char	*src;

	lst->par.cnt_set = 0;
	while (get_next_line(fd, &src))
		map_set_value(lst, src);
	map_set_value(lst, src);
	if (lst->par.cnt_set != 8)
		error();
	return (1);
}