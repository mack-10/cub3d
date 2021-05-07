/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:32:53 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/07 15:14:17 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	key_ws(int key, t_main *lst)
{
	if (key == KEY_W)
	{
		if (lst->par.map[(int)(lst->pos_x + lst->dir_x * lst->movespeed)]
			[(int)(lst->pos_y)] != 1)
			lst->pos_x += lst->dir_x * lst->movespeed;
		if (lst->par.map[(int)(lst->pos_x)]
			[(int)(lst->pos_y + lst->dir_y * lst->movespeed)] != 1)
			lst->pos_y += lst->dir_y * lst->movespeed;
	}
	else
	{
		if (lst->par.map[(int)(lst->pos_x - lst->dir_x * lst->movespeed)]
			[(int)(lst->pos_y)] != 1)
			lst->pos_x -= lst->dir_x * lst->movespeed;
		if (lst->par.map[(int)(lst->pos_x)]
			[(int)(lst->pos_y - lst->dir_y * lst->movespeed)] != 1)
			lst->pos_y -= lst->dir_y * lst->movespeed;
	}
}

static void	key_ad(int key, t_main *lst)
{
	if (key == KEY_A)
	{
		if (lst->par.map[(int)(lst->pos_x)]
			[(int)(lst->pos_y + lst->dir_x * lst->movespeed)] != 1)
			lst->pos_y += lst->dir_x * lst->movespeed;
		if (lst->par.map[(int)(lst->pos_x - lst->dir_y * lst->movespeed)]
			[(int)(lst->pos_y)] != 1)
			lst->pos_x -= lst->dir_y * lst->movespeed;
	}
	else
	{
		if (lst->par.map[(int)(lst->pos_x)]
			[(int)(lst->pos_y - lst->dir_x * lst->movespeed)] != 1)
			lst->pos_y -= lst->dir_x * lst->movespeed;
		if (lst->par.map[(int)(lst->pos_x + lst->dir_y * lst->movespeed)]
			[(int)(lst->pos_y)] != 1)
			lst->pos_x += lst->dir_y * lst->movespeed;
	}
}

static void	key_arrow(int key, t_main *lst, double olddirx, double oldplanex)
{
	if (key == KEY_AR_L)
	{
		lst->dir_x = lst->dir_x * cos(lst->rotspeed) - lst->dir_y
			* sin(lst->rotspeed);
		lst->dir_y = olddirx * sin(lst->rotspeed) + lst->dir_y
			* cos(lst->rotspeed);
		lst->plane_x = lst->plane_x * cos(lst->rotspeed) - lst->plane_y
			* sin(lst->rotspeed);
		lst->plane_y = oldplanex * sin(lst->rotspeed) + lst->plane_y
			* cos(lst->rotspeed);
	}
	else
	{
		lst->dir_x = lst->dir_x * cos(-lst->rotspeed) - lst->dir_y
			* sin(-lst->rotspeed);
		lst->dir_y = olddirx * sin(-lst->rotspeed) + lst->dir_y
			* cos(-lst->rotspeed);
		lst->plane_x = lst->plane_x * cos(-lst->rotspeed) - lst->plane_y
			* sin(-lst->rotspeed);
		lst->plane_y = oldplanex * sin(-lst->rotspeed) + lst->plane_y
			* cos(-lst->rotspeed);
	}
}

int			key_press(int key, t_main *lst)
{
	double olddirx;
	double oldplanex;

	olddirx = lst->dir_x;
	oldplanex = lst->plane_x;
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
