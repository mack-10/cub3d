/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:32:53 by sujeon            #+#    #+#             */
/*   Updated: 2021/04/21 20:40:09 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		key_w(t_val *lst)
{
	if (!worldMap[(int)(lst->posX + lst->dirX * lst->moveSpeed)]
		[(int)(lst->posY)])
		lst->posX += lst->dirX * lst->moveSpeed;
	if (!worldMap[(int)(lst->posX)]
		[(int)(lst->posY + lst->dirY * lst->moveSpeed)])
		lst->posY += lst->dirY * lst->moveSpeed;
}

static void		key_s(t_val *lst)
{
	if (!worldMap[(int)(lst->posX - lst->dirX * lst->moveSpeed)]
		[(int)(lst->posY)])
		lst->posX -= lst->dirX * lst->moveSpeed;
	if (!worldMap[(int)(lst->posX)]
		[(int)(lst->posY - lst->dirY * lst->moveSpeed)])
		lst->posY -= lst->dirY * lst->moveSpeed;
}

static void		key_a(t_val *lst)
{
	double olddirx;
	double oldplanex;

	olddirx = lst->dirX;
	oldplanex = lst->planeX;
	lst->dirX = lst->dirX * cos(lst->rotSpeed) - lst->dirY *
		sin(lst->rotSpeed);
	lst->dirY = olddirx * sin(lst->rotSpeed) + lst->dirY *
		cos(lst->rotSpeed);
	lst->planeX = lst->planeX * cos(lst->rotSpeed) - lst->planeY
	* sin(lst->rotSpeed);
	lst->planeY = oldplanex * sin(lst->rotSpeed) + lst->planeY
		* cos(lst->rotSpeed);
}

static void		key_d(t_val *lst)
{
	double olddirx;
	double oldplanex;

	olddirx = lst->dirX;
	oldplanex = lst->planeX;
	lst->dirX = lst->dirX * cos(-lst->rotSpeed) - lst->dirY *
		sin(-lst->rotSpeed);
	lst->dirY = olddirx * sin(-lst->rotSpeed) + lst->dirY *
		cos(-lst->rotSpeed);
	lst->planeX = lst->planeX * cos(-lst->rotSpeed) - lst->planeY *
		sin(-lst->rotSpeed);
	lst->planeY = oldplanex * sin(-lst->rotSpeed) + lst->planeY *
		cos(-lst->rotSpeed);
}

int				key_press(int key, t_val *lst)
{
	if (key == KEY_W)
		key_w(lst);
	if (key == KEY_S)
		key_s(lst);
	if (key == KEY_A)
		key_a(lst);
	if (key == KEY_D)
		key_d(lst);
	if (key == KEY_ESC)
		exit(0);
	return (0);
}
