/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:28:37 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/07 15:12:32 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			floor_ceiling(t_main *lst)
{
	int	x;
	int	y;

	y = 0;
	while (y < lst->par.screen_h / 2)
	{
		x = 0;
		while (x < lst->par.screen_w)
			lst->ray.buf[y][x++] = lst->par.c_color;
		y++;
	}
	while (y < lst->par.screen_h)
	{
		x = 0;
		while (x < lst->par.screen_w)
			lst->ray.buf[y][x++] = lst->par.f_color;
		y++;
	}
}
