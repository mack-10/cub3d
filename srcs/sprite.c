/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 03:49:55 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/03 03:06:33 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		set_spr(t_main *lst, t_sprite *spr, int i)
{
	spr->X = lst->par.spr_xy[i].x - lst->posX;
	spr->Y = lst->par.spr_xy[i].y - lst->posY;
	spr->invDet = 1.0 / (lst->planeX * lst->dirY - lst->dirX * lst->planeY);
	spr->transX = spr->invDet * (lst->dirY * spr->X - lst->dirX * spr->Y);
	spr->transY = spr->invDet * (-lst->planeY * spr->X + lst->planeX * spr->Y);
	spr->ScreenX = (int)((lst->par.screenW / 2) * (1 + spr->transX / spr->transY));
	spr->vMoveScreen = (int)(vMove / spr->transY);
	spr->spriteH = (int)fabs((lst->par.screenH / spr->transY) / vDiv);
	spr->drawStartY = -spr->spriteH / 2 + lst->par.screenH / 2 + spr->vMoveScreen;
	spr->drawEndY = spr->spriteH / 2 + lst->par.screenH / 2 + spr->vMoveScreen;
	spr->spriteW = (int)fabs((lst->par.screenH / spr->transY) / uDiv);
	spr->drawStartX = -spr->spriteW / 2 + spr->ScreenX;
	spr->drawEndX = spr->spriteW / 2 + spr->ScreenX;
	spr->stripe = spr->drawStartX;
}

static void		draw_sprite(t_main *lst, t_sprite *spr)
{
	while (spr->stripe < spr->drawEndX)
	{
		spr->texX = (int)((256 * (spr->stripe - (-spr->spriteW / 2 + spr->ScreenX)) * textureW
			/ spr->spriteW) / 256);
		if (spr->transY > 0 && spr->stripe > 0 && spr->stripe < lst->par.screenW
			&& spr->transY < lst->ray.zbuf[spr->stripe])
		{
			spr->y = spr->drawStartY;
			while (spr->y < spr->drawEndY)
			{
				spr->d = (spr->y - spr->vMoveScreen) * 256 - lst->par.screenH * 128
					+ spr->spriteH * 128;
				spr->texY = ((spr->d * textureH) / spr->spriteH) / 256;
				spr->color = lst->tex.texture[4][textureW * spr->texY + spr->texX];
				if (spr->color & 0x00FFFFFF)
					lst->ray.buf[spr->y][spr->stripe] = spr->color;
				spr->y++;
			}
		}
		spr->stripe++;
	}
}

static void		set_distance(t_main *lst, t_sprite *spr)
{
	int i;

	spr->distance = (double *)ft_calloc(lst->par.num_spr, sizeof(double));
	i = 0;
	while (i < lst->par.num_spr)
	{
		spr->distance[i] = ((lst->posX - lst->par.spr_xy[i].x) * (lst->posX - lst->par.spr_xy[i].x)
			+ (lst->posY - lst->par.spr_xy[i].y) * (lst->posY - lst->par.spr_xy[i].y));
		i++;
	}
}

void			sprite(t_main *lst)
{
	int			i;
	t_sprite	spr;

	set_distance(lst, &spr);
	i = 0;
	while (i < lst->par.num_spr)
	{
		set_spr(lst, &spr, i);
		if (spr.drawStartY < 0)
			spr.drawStartY = 0;		
		if (spr.drawEndY >= lst->par.screenH)
			spr.drawEndY = lst->par.screenH - 1;
		if (spr.drawStartX < 0)
			spr.drawStartX = 0;
		if (spr.drawEndX >=  lst->par.screenW)
			spr.drawEndX =  lst->par.screenW - 1;
		draw_sprite(lst, &spr);
		i++;
	}
	free(spr.distance);
}