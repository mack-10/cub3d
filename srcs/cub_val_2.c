/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_val_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 02:49:03 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/06 23:34:30 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		screen_size(t_main *lst, char **split)
{
	lst->par.screenW = ft_atoi(split[1]);
	lst->par.screenH = ft_atoi(split[2]);
	if (lst->par.screenW <= 0 || lst->par.screenH <= 0)
		error();
	if (lst->par.screenW > lst->max_w)
		lst->par.screenW = lst->max_w;
	if (lst->par.screenH > lst->max_h)
		lst->par.screenH = lst->max_h;
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
