/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:32:12 by sujeon            #+#    #+#             */
/*   Updated: 2021/04/21 20:46:56 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	ray->lineHeight = (int)(screenH / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + screenH / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + screenH / 2;
	if (ray->drawEnd >= screenH)
		ray->drawEnd = screenH - 1;
}

static void		draw(t_val *lst)
{
	int x;
	int y;

	y = 0;
	while (y < screenH)
	{
		x = 0;
		while (x < screenW)
		{
			lst->img.data[y * screenW + x] = lst->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(lst->mlx, lst->win, lst->img.img, 0, 0);
}

int				ray_c(t_val *lst)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < screenW)
	{
		ray.cameraX = 2 * x / (double)screenW - 1;
		ray.rayDirX = lst->dirX + lst->planeX * ray.cameraX;
		ray.rayDirY = lst->dirY + lst->planeY * ray.cameraX;
		ray.mapX = (int)(lst->posX);
		ray.mapY = (int)(lst->posY);
		ray.deltaDistX = fabs(1 / ray.rayDirX);
		ray.deltaDistY = fabs(1 / ray.rayDirY);
		ray.hit = 0;
		step(lst, &ray);
		dda(&ray);
		perp_line(lst, &ray);
		texture(lst, &ray, x);
		x++;
	}
	draw(lst);
	return (0);
}
