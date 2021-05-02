/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 23:07:10 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/03 02:16:31 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		map_char_int(t_main *lst, t_par *par)
{
	int i;
	int j;
	int idx;
	
	i = -1;
	idx = 0;
	while (++i < par->map_h)
	{
		j = -1;
		printf("map |");
		while (++j < par->map_w[i])
		{
			if (par->map_double[i][j] == '1')
				par->map[i][j] = 1;
			else if (par->map_double[i][j] == '0' || par->map_double[i][j] == ' ')
				par->map[i][j] = 0;
			else if (par->map_double[i][j] == '2')
			{
				par->map[i][j] = 2;
				lst->par.num_spr++;
				lst->par.spr_xy[idx].x = i;
				lst->par.spr_xy[idx].y = j;
				idx++;
			}
			else
			{
				lst->posX = i;
				lst->posY = j;
				par->map[i][j] = 0;
			}
			printf("%d", par->map[i][j]);
		}
		printf("\n");
	}
}

static void		map_h_w(t_par *par)
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

void			split_map(t_main *lst, t_par *par)
{
	int i;

	par->map_double = NULL;
	par->map_double = ft_split(par->map_one, '\n');
	i = 0;
	while (par->map_one[i])
	{
		if (par->map_one[i] == '2')
			lst->par.num_spr++;
		i++;
	}
	free_one(par->map_one);

	map_h_w(par);
	
	par->map = (int **)ft_calloc(par->map_h, sizeof(int *));
	i = 0;
	while (i < par->map_h)
	{
		par->map[i] = (int *)ft_calloc(par->map_w[i], sizeof(int));
		i++;
	}
	lst->par.spr_xy = (t_xy *)ft_calloc(lst->par.num_spr, sizeof(t_xy));
	map_char_int(lst, par);
}