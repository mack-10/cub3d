/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:32:16 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/07 15:09:28 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		put_buf(t_main *lst, int x)
{
	int y;

	y = lst->ray.drawStart;
	while (y < lst->ray.drawEnd)
	{
		lst->tex.tex_y = (int)lst->tex.tex_pos & (TEXTUREW - 1);
		lst->tex.tex_pos += lst->tex.step;
		lst->tex.color = lst->tex.texture[lst->tex.texnum]
			[TEXTUREW * lst->tex.tex_y + lst->tex.tex_x];
		if (lst->ray.side == 1)
			lst->tex.color = (lst->tex.color >> 1) & 8355711;
		lst->ray.buf[y][x] = lst->tex.color;
		y++;
	}
}

static void		tex_nswe(t_main *lst)
{
	if (!lst->ray.side)
	{
		if (lst->posX > lst->ray.mapX)
			lst->tex.texnum = 0;
		else
			lst->tex.texnum = 1;
	}
	else
	{
		if (lst->posY > lst->ray.mapY)
			lst->tex.texnum = 2;
		else
			lst->tex.texnum = 3;
	}
}

void			print_tex(t_main *lst, int x)
{
	if (lst->ray.side == 0)
		lst->tex.wall_x = lst->posY + lst->ray.perpWallDist
			* lst->ray.rayDirY;
	else
		lst->tex.wall_x = lst->posX + lst->ray.perpWallDist
			* lst->ray.rayDirX;
	lst->tex.wall_x -= floor(lst->tex.wall_x);
	lst->tex.tex_x = (int)(lst->tex.wall_x * (double)TEXTUREW);
	if (lst->ray.side == 0 && lst->ray.rayDirX > 0)
		lst->tex.tex_x = TEXTUREW - lst->tex.tex_x - 1;
	if (lst->ray.side == 1 && lst->ray.rayDirY < 0)
		lst->tex.tex_x = TEXTUREW - lst->tex.tex_x - 1;
	lst->tex.step = 1.0 * TEXTUREW / lst->ray.lineHeight;
	lst->tex.tex_pos = (lst->ray.drawStart - lst->par.screenH
		/ 2 + lst->ray.lineHeight / 2) * lst->tex.step;
	tex_nswe(lst);
	put_buf(lst, x);
}
