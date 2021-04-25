/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:32:12 by sujeon            #+#    #+#             */
/*   Updated: 2021/04/25 21:20:30 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		draw(t_val *lst)
{
	int x;
	int y;

	y = 0;
	while (y < lst->screenH)
	{
		x = 0;
		while (x < lst->screenW)
		{
			lst->img.data[y * lst->screenW + x] = lst->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(lst->mlx, lst->win, lst->img.img, 0, 0);
}

static void		step(t_val *lst, t_ray *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (lst->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - lst->posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (lst->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - lst->posY) * ray->deltaDistY;
	}
}

static void		dda(t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (worldMap[ray->mapX][ray->mapY] > 0)
			ray->hit = 1;
	}
}

static void		perp_line(t_val *lst, t_ray *ray)
{
	if (ray->side == 0)
		ray->perpWallDist =
		(ray->mapX - lst->posX + (1 - ray->stepX) / 2) / ray->rayDirX;
	else
		ray->perpWallDist =
		(ray->mapY - lst->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
	ray->lineHeight = (int)(lst->screenH / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + lst->screenH / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + lst->screenH / 2;
	if (ray->drawEnd >= lst->screenH)
		ray->drawEnd = lst->screenH - 1;
}

int				ray_c(t_val *lst)
{
	t_ray	ray;
	int		x;
	
	set_buf(lst);
	floor_ceiling(lst);
	x = 0;
	while (x < lst->screenW)
	{
		set_ray(lst, &ray, x);
		step(lst, &ray);
		dda(&ray);
		perp_line(lst, &ray);
		print_tex(lst, &ray, x);
		x++;
	}
	draw(lst);
	return (0);
}
