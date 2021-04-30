/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 16:27:01 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/01 05:18:15 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_val(char **s)
{
	int	i;
	int n;
	
	if (s[0][0] == 'R')
		n = 3;
	else
		n = 2;
	i = 0;
	while (s[i])
		i++;
	if (n != i)
		return (0);
	return (1);
}

static void	tex_path(t_par *par, char **split)
{
	if (split[0][0] == 'N' && split[0][1] == 'O')
		par->tex_path[0] = ft_strdup(split[1]);
	else if (split[0][0] == 'S' && split[0][1] == 'O')
		par->tex_path[1] = ft_strdup(split[1]);
	else if (split[0][0] == 'W' && split[0][1] == 'E')
		par->tex_path[2] = ft_strdup(split[1]);
	else if (split[0][0] == 'E' && split[0][1] == 'A')
		par->tex_path[3] = ft_strdup(split[1]);
	else
		par->s_path = ft_strdup(split[1]);
}

static void	get_value(t_par *par, char **split)
{
	if (check_val(split))
	{
			if (split[0][0] == 'R')
		{
			par->screenW = ft_atoi(split[1]);
			par->screenH = ft_atoi(split[2]);
		}
		else if (split[0][0] == 'F')
			par->f_rgb = ft_strdup(split[1]);
		else if (split[0][0] == 'C')
			par->c_rgb = ft_strdup(split[1]);
		else
			tex_path(par, split);
	}
	else
	{
		free_double(split);
		error();
	}
}

static void	map_set_value(t_par *par, char *src)
{
	char	**split;
	char	*tmp;
	
	if (src[0] == '1' || src[0] == ' ')
	{
		tmp = g_strjoin(par->map_one, src);
		free_one(par->map_one);
		par->map_one = g_strjoin(tmp, "\n");
		free_one(tmp);
	}
	else if (src[0] >= 'A')
	{
		split = ft_split(src, ' ');
		get_value(par, split);
		par->cnt_set++;
		free_double(split);
	}
	free_one(src);
}

static void split_map(t_par *par)
{
	int i;

	i = 0;
	while (par->map_one[i])
	{
		if (par->map_one[i] == '\n')
			par->map_h++;
		i++;
	}
	printf("h|%d\n", par->map_h);
	par->map_double = ft_split(par->map_one, '\n');
	free_one(par->map_one);
	
	i = 0;
	while (par->map_double[i])
	{
		printf("map[%d] |%s\n", i, par->map_double[i]);
		i++;
	}
}

int			 parsing(t_main *lst, int fd)
{
	char	*src;

	lst->par.cnt_set = 0;
	lst->par.map_one = g_strjoin("", "");
	while (get_next_line(fd, &src))
		map_set_value(&lst->par, src);
	map_set_value(&lst->par, src);
	split_map(&lst->par);
	if (lst->par.cnt_set != 8)
		error();
	return (1);
}