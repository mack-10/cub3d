/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 02:29:52 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/07 15:12:30 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			draw(t_main *lst)
{
	int x;
	int y;

	y = 0;
	while (y < lst->par.screen_h)
	{
		x = 0;
		while (x < lst->par.screen_w)
		{
			lst->img.data[(y * lst->par.screen_w) + x] = lst->ray.buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(lst->mlx, lst->win, lst->img.img, 0, 0);
}
