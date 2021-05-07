/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 02:44:00 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/07 15:14:15 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	g_dirx[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int	g_diry[8] = {0, 1, 0, -1, -1, 1, 1, -1};

static int	parsing_map(char **map, int x, int y)
{
	int i;

	if (map[y][x] == '1' || map[y][x] == 'x')
		return (1);
	if (map[y][x] == ' ')
		return (0);
	map[y][x] = 'x';
	i = -1;
	while (++i < 8)
		if (!parsing_map(map, x + g_dirx[i], y + g_diry[i]))
			return (0);
	return (1);
}

static void	set_test_map(t_par *par)
{
	int i;
	int big_w;

	big_w = 0;
	i = -1;
	while (++i < par->map_h)
	{
		if (par->map_w[i] > big_w)
			big_w = par->map_w[i];
	}
	par->test_map = (char **)ft_calloc(par->map_h + 2 + 1, sizeof(char *));
	i = -1;
	while (++i < par->map_h + 2)
	{
		par->test_map[i] = (char *)ft_calloc(big_w + 2 + 1, sizeof(char));
		ft_memset(par->test_map[i], ' ', big_w + 2);
		par->test_map[i][big_w + 2] = 0;
	}
	par->test_map[i] = 0;
	i = 0;
	while (++i < par->map_h + 1)
		ft_memcpy(par->test_map[i] + 1, par->map_double[i - 1],
			ft_strlen(par->map_double[i - 1]));
}

static void	nswe_val(t_main *lst, t_par *par)
{
	if (par->orient == 'N')
	{
		lst->dir_x = -1.0;
		lst->plane_y = 0.66;
	}
	if (par->orient == 'S')
	{
		lst->dir_x = 1.0;
		lst->plane_y = -0.66;
	}
	if (par->orient == 'W')
	{
		lst->dir_y = -1.0;
		lst->plane_x = -0.66;
	}
	if (par->orient == 'E')
	{
		lst->dir_y = 1.0;
		lst->plane_x = 0.66;
	}
}

static void	search_nswe(t_main *lst, t_par *par)
{
	int i;
	int j;

	par->orient = 0;
	i = -1;
	while (par->map_double[++i])
	{
		j = -1;
		while (par->map_double[i][++j])
		{
			if (par->map_double[i][j] == 'N' ||
				par->map_double[i][j] == 'S' ||
				par->map_double[i][j] == 'W' ||
				par->map_double[i][j] == 'E')
			{
				par->orient = par->map_double[i][j];
				nswe_val(lst, par);
				par->sign_orient++;
			}
		}
	}
	if (!par->sign_orient || par->sign_orient > 1)
		error();
}

void		check_map(t_main *lst, t_par *par)
{
	int x;
	int y;

	search_nswe(lst, par);
	set_test_map(par);
	y = -1;
	while (par->test_map[++y])
	{
		x = -1;
		while (par->test_map[y][++x])
		{
			if (par->test_map[y][x] == '0')
			{
				if (!parsing_map(par->test_map, x, y))
					error();
			}
		}
	}
	free_double(par->test_map);
}
