/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:28:37 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/01 04:28:05 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		rgb_hex(char *src)
{
	char	**split;
	int		rgb[3];
	int		color;
	int		i;

	split = ft_split(src, ',');
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(split[i]);
		i++;
	}
	free_double(split);
	color = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	return (color);
}

void			floor_ceiling(t_main *lst)
{
	int	x;
	int	y;
	int	c_color;
	int f_color;
	
	f_color = rgb_hex(lst->par.f_rgb);
	c_color = rgb_hex(lst->par.c_rgb);
	y = 0;
	while (y < lst->par.screenH)
	{
		x = 0;
		while (++x < lst->par.screenW)
		{
			lst->ray.buf[y][x] = c_color;
			lst->ray.buf[lst->par.screenH - y - 1][x] = f_color;
		}
		y++;
	}
}