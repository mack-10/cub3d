/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:32:12 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/07 15:12:35 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		step(t_main *lst)
{
	if (lst->ray.raydir_x < 0)
	{
		lst->ray.step_x = -1;
		lst->ray.sidedist_x = (lst->posX - lst->ray.map_x) * lst->ray.deltadist_x;
	}
	else
	{
		lst->ray.step_x = 1;
		lst->ray.sidedist_x = (lst->ray.map_x + 1.0 - lst->posX) *
			lst->ray.deltadist_x;
	}
	if (lst->ray.raydir_y < 0)
	{
		lst->ray.step_y = -1;
		lst->ray.sidedist_y = (lst->posY - lst->ray.map_y) * lst->ray.deltadist_y;
	}
	else
	{
		lst->ray.step_y = 1;
		lst->ray.sidedist_y = (lst->ray.map_y + 1.0 - lst->posY) *
			lst->ray.deltadist_y;
	}
}

static void		dda(t_main *lst)
{
	while (lst->ray.hit == 0)
	{
		if (lst->ray.sidedist_x < lst->ray.sidedist_y)
		{
			lst->ray.sidedist_x += lst->ray.deltadist_x;
			lst->ray.map_x += lst->ray.step_x;
			lst->ray.side = 0;
		}
		else
		{
			lst->ray.sidedist_y += lst->ray.deltadist_y;
			lst->ray.map_y += lst->ray.step_y;
			lst->ray.side = 1;
		}
		if (lst->par.map[lst->ray.map_x][lst->ray.map_y] == 1)
			lst->ray.hit = 1;
	}
}

static void		perp_line(t_main *lst, int x)
{
	if (lst->ray.side == 0)
		lst->ray.perpwalldist = (lst->ray.map_x - lst->posX +
			(1 - lst->ray.step_x) / 2) / lst->ray.raydir_x;
	else
		lst->ray.perpwalldist = (lst->ray.map_y - lst->posY +
			(1 - lst->ray.step_y) / 2) / lst->ray.raydir_y;
	lst->ray.lineheight = (int)(lst->par.screen_h / lst->ray.perpwalldist);
	lst->ray.drawstart = -lst->ray.lineheight / 2 + lst->par.screen_h / 2;
	if (lst->ray.drawstart < 0)
		lst->ray.drawstart = 0;
	lst->ray.drawend = lst->ray.lineheight / 2 + lst->par.screen_h / 2;
	if (lst->ray.drawend >= lst->par.screen_h)
		lst->ray.drawend = lst->par.screen_h - 1;
}

void			raycasting(t_main *lst)
{
	int		x;

	set_buf(lst);
	floor_ceiling(lst);
	x = 0;
	while (x < lst->par.screen_w)
	{
		set_ray(lst, x);
		step(lst);
		dda(lst);
		perp_line(lst, x);
		print_tex(lst, x);
		lst->ray.zbuf[x] = lst->ray.perpwalldist;
		x++;
	}
}
