/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 02:29:52 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/03 02:35:23 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		free_buf(t_main *lst)
{
	int i;

	i = 0;
	while (i < lst->par.screenH)
	{
		free(lst->ray.buf[i]);
		i++;
	}
	free(lst->ray.buf);
}

void			draw(t_main *lst)
{
	int x;
	int y;

	y = 0;
	while (y < lst->par.screenH)
	{
		x = 0;
		while (x < lst->par.screenW)
		{
			lst->img.data[y * lst->par.screenW + x] = lst->ray.buf[y][x];
			x++;
		}
		y++;
	}
	free_buf(lst);
	mlx_put_image_to_window(lst->mlx, lst->win, lst->img.img, 0, 0);
}