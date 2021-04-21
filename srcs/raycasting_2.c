/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:32:16 by sujeon            #+#    #+#             */
/*   Updated: 2021/04/21 20:48:47 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		buf(t_val *lst, t_ray *ray, t_tex *tex, int x)
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

void			texture(t_val *lst, t_ray *ray, int x)
{
	t_tex	tex;

	tex.texNum = worldMap[ray->mapX][ray->mapY] - 1;
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
	buf(lst, ray, &tex, x);
}
