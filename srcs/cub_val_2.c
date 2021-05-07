/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_val_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 02:49:03 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/07 15:12:33 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		screen_size(t_main *lst, char **split)
{
	lst->par.screen_w = ft_atoi(split[1]);
	lst->par.screen_h = ft_atoi(split[2]);
	if (lst->par.screen_w <= 0 || lst->par.screen_h <= 0)
		error();
	if (lst->par.screen_w > lst->max_w)
		lst->par.screen_w = lst->max_w;
	if (lst->par.screen_h > lst->max_h)
		lst->par.screen_h = lst->max_h;
	lst->par.sign_val[0] = 1;
}

int			rgb_hex(char *src)
{
	char	**split;
	int		rgb[3];
	int		color;
	int		i;

	split = ft_split(src, ',');
	i = -1;
	while (split[++i])
		;
	if (i != 3)
		error();
	i = -1;
	while (++i < 3)
	{
		rgb[i] = ft_atoi(split[i]);
		if (!(rgb[i] >= 0 && rgb[i] <= 255))
			error();
	}
	free_double(split);
	color = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	return (color);
}
