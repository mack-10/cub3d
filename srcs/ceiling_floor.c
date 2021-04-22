/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:28:37 by sujeon            #+#    #+#             */
/*   Updated: 2021/04/22 18:28:50 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		print_fc(t_val *lst, t_fc *fc, int y)
{
	int x;
	
	x = 0;
	while (++x < screenW)
	{
		fc->cellX = (int)(fc->floorX);
		fc->cellY = (int)(fc->floorY);
		fc->color = 0xFFFFFF;
		lst->buf[y][x] = fc->color;
		fc->color = 0x000080;
		lst->buf[screenH - y - 1][x] = fc->color;
	}
}

void			floor_ceiling(t_val *lst)
{
	t_fc fc;
	int y;
	
	y = 0;
	while (y < screenH)
	{
		fc.rayDirX0 = lst->dirX - lst->planeX;
		fc.rayDirY0 = lst->dirY - lst->planeY;
		fc.rayDirX1 = lst->dirX + lst->planeX;
		fc.rayDirY1 = lst->dirY + lst->planeY;
		fc.p = y - screenH / 2;
		fc.posZ = 0.5 * screenH;
		fc.rowDistance = fc.posZ / fc.p;
		fc.floorStepX = fc.rowDistance * (fc.rayDirX1 - fc.rayDirX0) / screenW;
		fc.floorStepY = fc.rowDistance * (fc.rayDirY1 - fc.rayDirY0) / screenW;
		fc.floorX = lst->posX + fc.rowDistance * fc.rayDirX0;
		fc.floorY = lst->posY + fc.rowDistance * fc.rayDirY0;
		print_fc(lst, &fc, y);
		y++;
	}
}