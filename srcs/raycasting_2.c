/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:32:16 by sujeon            #+#    #+#             */
/*   Updated: 2021/04/22 16:54:38 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		put_buf(t_val *lst, t_ray *ray, t_tex *tex, int x)
{
	int y;

	y = ray->drawStart;
	while (y < ray->drawEnd)
	{
		tex->texY = (int)tex->texPos & (textureH - 1);
		tex->texPos += tex->step;
		tex->color = lst->texture[tex->texNum]
			[textureH * tex->texY + tex->texX];
		if (ray->side == 1)
			tex->color = (tex->color >> 1) & 8355711;
		lst->buf[y][x] = tex->color;
		y++;
	}
}

void			print_tex(t_val *lst, t_ray *ray, int x)
{
	t_tex	tex;

	if (!ray->side)
	{
		if (ray->mapX % 2 == 1)
			tex.texNum = 0;
		else
			tex.texNum = 1;
	}		
	else
	{
		if (ray->mapY % 2 == 1)
			tex.texNum = 2;
		else
			tex.texNum = 3;
	}
	if (ray->side == 0)
		tex.wallX = lst->posY + ray->perpWallDist * ray->rayDirY;
	else
		tex.wallX = lst->posX + ray->perpWallDist * ray->rayDirX;
	tex.wallX -= floor(tex.wallX);
	tex.texX = (int)(tex.wallX * (double)textureW);
	if (ray->side == 0 && ray->rayDirX > 0)
		tex.texX = textureW - tex.texX - 1;
	if (ray->side == 1 && ray->rayDirY < 0)
		tex.texX = textureW - tex.texX - 1;
	tex.step = 1.0 * textureH / ray->lineHeight;
	tex.texPos = (ray->drawStart - screenH / 2 + ray->lineHeight / 2)
		* tex.step;
	put_buf(lst, ray, &tex, x);
}

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
	int x;
	
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