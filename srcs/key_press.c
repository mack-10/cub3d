/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:32:53 by sujeon            #+#    #+#             */
/*   Updated: 2021/04/18 17:33:19 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int key, t_val *lst)
{
	if (key == KEY_W)
	{
		if (!worldMap[(int)(lst->posX + lst->dirX * lst->moveSpeed)][(int)(lst->posY)])
			lst->posX += lst->dirX * lst->moveSpeed;
		if (!worldMap[(int)(lst->posX)][(int)(lst->posY + lst->dirY * lst->moveSpeed)])
			lst->posY += lst->dirY * lst->moveSpeed;
	}
	if (key == KEY_S)
	{
		if (!worldMap[(int)(lst->posX - lst->dirX * lst->moveSpeed)][(int)(lst->posY)])
			lst->posX -= lst->dirX * lst->moveSpeed;
		if (!worldMap[(int)(lst->posX)][(int)(lst->posY - lst->dirY * lst->moveSpeed)])
			lst->posY -= lst->dirY * lst->moveSpeed;
	}
	if (key == KEY_D)
	{
		double oldDirX = lst->dirX;
		lst->dirX = lst->dirX * cos(-lst->rotSpeed) - lst->dirY * sin(-lst->rotSpeed);
		lst->dirY = oldDirX * sin(-lst->rotSpeed) + lst->dirY * cos(-lst->rotSpeed);
		double oldPlaneX = lst->planeX;
		lst->planeX = lst->planeX * cos(-lst->rotSpeed) - lst->planeY * sin(-lst->rotSpeed);
		lst->planeY = oldPlaneX * sin(-lst->rotSpeed) + lst->planeY * cos(-lst->rotSpeed);
	}
	if (key == KEY_A)
	{
		double oldDirX = lst->dirX;
		lst->dirX = lst->dirX * cos(lst->rotSpeed) - lst->dirY * sin(lst->rotSpeed);
		lst->dirY = oldDirX * sin(lst->rotSpeed) + lst->dirY * cos(lst->rotSpeed);
		double oldPlaneX = lst->planeX;
		lst->planeX = lst->planeX * cos(lst->rotSpeed) - lst->planeY * sin(lst->rotSpeed);
		lst->planeY = oldPlaneX * sin(lst->rotSpeed) + lst->planeY * cos(lst->rotSpeed);
	}
	if (key == KEY_ESC)
		exit(0);
	return (0);
}