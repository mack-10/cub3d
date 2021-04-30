/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:32:12 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/01 04:13:02 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		draw(t_main *lst)
{
	int x;
	int y;
	int i;

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
	i = 0;
	while (i < lst->par.screenH)
	{
		free(lst->ray.buf[i]);
		i++;
	}
	free(lst->ray.buf);
	mlx_put_image_to_window(lst->mlx, lst->win, lst->img.img, 0, 0);
}

static void		step(t_main *lst)
{
	if (lst->ray.rayDirX < 0)
	{
		lst->ray.stepX = -1;
		lst->ray.sideDistX = (lst->posX - lst->ray.mapX) * lst->ray.deltaDistX;
	}
	else
	{
		lst->ray.stepX = 1;
		lst->ray.sideDistX = (lst->ray.mapX + 1.0 - lst->posX) * lst->ray.deltaDistX;
	}
	if (lst->ray.rayDirY < 0)
	{
		lst->ray.stepY = -1;
		lst->ray.sideDistY = (lst->posY - lst->ray.mapY) * lst->ray.deltaDistY;
	}
	else
	{
		lst->ray.stepY = 1;
		lst->ray.sideDistY = (lst->ray.mapY + 1.0 - lst->posY) * lst->ray.deltaDistY;
	}
}

static void		dda(t_main *lst)
{
	while (lst->ray.hit == 0)
	{
		if (lst->ray.sideDistX < lst->ray.sideDistY)
		{
			lst->ray.sideDistX += lst->ray.deltaDistX;
			lst->ray.mapX += lst->ray.stepX;
			lst->ray.side = 0;
		}
		else
		{
			lst->ray.sideDistY += lst->ray.deltaDistY;
			lst->ray.mapY += lst->ray.stepY;
			lst->ray.side = 1;
		}
		if (worldMap[lst->ray.mapX][lst->ray.mapY] > 0)
			lst->ray.hit = 1;
	}
}

static void		perp_line(t_main *lst)
{
	if (lst->ray.side == 0)
		lst->ray.perpWallDist =
		(lst->ray.mapX - lst->posX + (1 - lst->ray.stepX) / 2) / lst->ray.rayDirX;
	else
		lst->ray.perpWallDist =
		(lst->ray.mapY - lst->posY + (1 - lst->ray.stepY) / 2) / lst->ray.rayDirY;
	lst->ray.lineHeight = (int)(lst->par.screenH / lst->ray.perpWallDist);
	lst->ray.drawStart = -lst->ray.lineHeight / 2 + lst->par.screenH / 2;
	if (lst->ray.drawStart < 0)
		lst->ray.drawStart = 0;
	lst->ray.drawEnd = lst->ray.lineHeight / 2 + lst->par.screenH / 2;
	if (lst->ray.drawEnd >= lst->par.screenH)
		lst->ray.drawEnd = lst->par.screenH - 1;
}

int				ray_c(t_main *lst)
{
	int		x;
	
	set_buf(lst);
	floor_ceiling(lst);
	x = 0;
	while (x < lst->par.screenW)
	{
		set_ray(lst, x);
		step(lst);
		dda(lst);
		perp_line(lst);
		print_tex(lst, x);
		x++;
	}
	draw(lst);
	return (0);
}
