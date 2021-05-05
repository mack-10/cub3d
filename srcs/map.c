/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 23:07:10 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/05 21:37:39 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	char_to_int(t_main *lst, int i, int j, int idx)
{
	if (lst->par.map_double[i][j] == '1')
		lst->par.map[i][j] = 1;
	else if (lst->par.map_double[i][j] == '0' || lst->par.map_double[i][j] == ' ')
		lst->par.map[i][j] = 0;
	else if (lst->par.map_double[i][j] == '2')
	{
		lst->par.map[i][j] = 2;
		lst->par.sprpos[idx].x = i + 0.5;
		lst->par.sprpos[idx].y = j + 0.5;
		idx++;
	}
	else if (lst->par.map_double[i][j] == lst->par.orient)
	{
		lst->posX = i + 0.5;
		lst->posY = j + 0.5;
		lst->par.map[i][j] = 0;
	}
	else
		error();
	return (idx);
}

static void	put_map(t_main *lst, t_par *par)
{
	int i;
	int j;
	int idx;
	
	i = -1;
	idx = 0;
	while (++i < par->map_h)
	{
		j = -1;
		while (++j < par->map_w[i])
			idx = char_to_int(lst, i, j, idx);
	}
}

static void	map_h_w(t_par *par)
{
	int i;

	par->map_h = 0;
	while (par->map_double[par->map_h])
		par->map_h++;
	par->map_w = (int *)ft_calloc(par->map_h + 1, sizeof(int));
	i = 0;
	while (i < par->map_h)
		par->map_w[i++] = 0;
	i = 0;
	while (i < par->map_h)
	{
		par->map_w[i] = ft_strlen(par->map_double[i]);
		i++;
	}
}

static void	split_map(t_par *par)
{
	int i;

	par->map_double = NULL;
	par->map_double = ft_split(par->map_one, '\n');
	i = 0;
	while (par->map_one[i])
	{
		if (par->map_one[i] == '2')
			par->spr_num++;
		i++;
	}
	free_one(par->map_one);
}

void		map(t_main *lst, t_par *par)
{
	split_map(par);
	map_h_w(par);
	check_map(lst, par);
	set_map(lst, par);
	put_map(lst, par);
}