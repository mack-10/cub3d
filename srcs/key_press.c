/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:32:53 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/02 17:52:53 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		key_ws(int key, t_main *lst)
{
	if (key == KEY_W)
	{
		if (lst->par.map[(int)(lst->posX + lst->dirX * lst->moveSpeed)]
			[(int)(lst->posY)] != 1)
			lst->posX += lst->dirX * lst->moveSpeed;
		if (lst->par.map[(int)(lst->posX)]
			[(int)(lst->posY + lst->dirY * lst->moveSpeed)] != 1)
			lst->posY += lst->dirY * lst->moveSpeed;
	}
	else
	{
		if (lst->par.map[(int)(lst->posX - lst->dirX * lst->moveSpeed)]
			[(int)(lst->posY)] != 1)
			lst->posX -= lst->dirX * lst->moveSpeed;
		if (lst->par.map[(int)(lst->posX)]
			[(int)(lst->posY - lst->dirY * lst->moveSpeed)] != 1)
			lst->posY -= lst->dirY * lst->moveSpeed;
	}
}

static void		key_ad(int key, t_main *lst)
{
	if (key == KEY_A)
	{
		if (lst->par.map[(int)(lst->posX)]
			[(int)(lst->posY + lst->dirX * lst->moveSpeed)] != 1)
			lst->posY += lst->dirX * lst->moveSpeed;		
		if (lst->par.map[(int)(lst->posX - lst->dirY * lst->moveSpeed)]
			[(int)(lst->posY)] != 1)
			lst->posX -= lst->dirY * lst->moveSpeed;
	}	
	else
	{
		if (lst->par.map[(int)(lst->posX)]
			[(int)(lst->posY - lst->dirX * lst->moveSpeed)] != 1)
			lst->posY -= lst->dirX * lst->moveSpeed;
		if (lst->par.map[(int)(lst->posX + lst->dirY * lst->moveSpeed)]
			[(int)(lst->posY)] != 1)
			lst->posX += lst->dirY * lst->moveSpeed;
	}
}

static void		key_arrow(int key, t_main *lst, double olddirx, double oldplanex)
{
	if (key == KEY_AR_L)
	{
		lst->dirX = lst->dirX * cos(lst->rotSpeed) - lst->dirY 
			* sin(lst->rotSpeed);
		lst->dirY = olddirx * sin(lst->rotSpeed) + lst->dirY
			* cos(lst->rotSpeed);
		lst->planeX = lst->planeX * cos(lst->rotSpeed) - lst->planeY
			* sin(lst->rotSpeed);
		lst->planeY = oldplanex * sin(lst->rotSpeed) + lst->planeY
			* cos(lst->rotSpeed);
	}
	else
	{	
		lst->dirX = lst->dirX * cos(-lst->rotSpeed) - lst->dirY 
			* sin(-lst->rotSpeed); 
		lst->dirY = olddirx * sin(-lst->rotSpeed) + lst->dirY 
			* cos(-lst->rotSpeed);
		lst->planeX = lst->planeX * cos(-lst->rotSpeed) - lst->planeY 
			* sin(-lst->rotSpeed);
		lst->planeY = oldplanex * sin(-lst->rotSpeed) + lst->planeY 
			* cos(-lst->rotSpeed);
	}
}

int				key_press(int key, t_main *lst)
{
	double olddirx;
	double oldplanex;

	olddirx = lst->dirX;
	oldplanex = lst->planeX;
	if (key == KEY_W || key == KEY_S)
		key_ws(key, lst);
	else if (key == KEY_A || key == KEY_D)
		key_ad(key, lst);
	else if (key == KEY_AR_L || key == KEY_AR_R)
		key_arrow(key, lst, olddirx, oldplanex);
	else if (key == KEY_ESC)
		exit(0);
	return (0);
}
