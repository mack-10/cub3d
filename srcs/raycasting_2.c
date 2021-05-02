/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:32:16 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/03 02:36:07 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		put_buf(t_main *lst, int x)
{
	int y;
	
	y = lst->ray.drawStart;
	while (y < lst->ray.drawEnd)
	{
		lst->tex.texY = (int)lst->tex.texPos & (textureH - 1);
		lst->tex.texPos += lst->tex.step;
		lst->tex.color = lst->tex.texture[lst->tex.texNum]
			[textureH * lst->tex.texY + lst->tex.texX];
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
			lst->tex.texNum = 0;
		else
			lst->tex.texNum = 1;
	}		
	else
	{
		if (lst->posY > lst->ray.mapY)
			lst->tex.texNum = 2;
		else
			lst->tex.texNum = 3;
	}
}

void			print_tex(t_main *lst, int x)
{	
	if (lst->ray.side == 0)
		lst->tex.wallX = lst->posY + lst->ray.perpWallDist 
			* lst->ray.rayDirY;
	else
		lst->tex.wallX = lst->posX + lst->ray.perpWallDist
			* lst->ray.rayDirX;
	lst->tex.wallX -= floor(lst->tex.wallX);
	lst->tex.texX = (int)(lst->tex.wallX * (double)textureW);
	if (lst->ray.side == 0 && lst->ray.rayDirX > 0)
		lst->tex.texX = textureW - lst->tex.texX - 1;
	if (lst->ray.side == 1 && lst->ray.rayDirY < 0)
		lst->tex.texX = textureW - lst->tex.texX - 1;
	lst->tex.step = 1.0 * textureH / lst->ray.lineHeight;
	lst->tex.texPos = (lst->ray.drawStart - lst->par.screenH
		/ 2 + lst->ray.lineHeight / 2) * lst->tex.step;
	tex_nswe(lst);
	put_buf(lst, x);
}
