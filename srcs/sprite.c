/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 03:49:55 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/04 06:10:24 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		set_spr(t_main *lst, t_spr *spr, int i)
{
	t_sprpos	*pos;
	
	pos = lst->par.sprpos;
	spr->X = pos[i].x - lst->posX;
	spr->Y = pos[i].y - lst->posY;
	spr->invDet = 1.0 / (lst->planeX * lst->dirY - lst->dirX * lst->planeY);
	spr->transX = spr->invDet * (lst->dirY * spr->X - lst->dirX * spr->Y);
	spr->transY = spr->invDet * (-lst->planeY * spr->X + lst->planeX * spr->Y);
	spr->ScreenX = (int)((lst->par.screenW / 2) * (1 + spr->transX / spr->transY));
	spr->spriteH = (int)fabs(lst->par.screenH / spr->transY);
	spr->spriteW = (int)fabs(lst->par.screenH / spr->transY);
	spr->drawStartX = -spr->spriteW / 2 + spr->ScreenX;
	spr->drawStartY = -spr->spriteH / 2 + lst->par.screenH / 2;
	spr->drawEndX = spr->spriteW / 2 + spr->ScreenX;
	spr->drawEndY = spr->spriteH / 2 + lst->par.screenH / 2;
	spr->stripe = spr->drawStartX;
}

static void	sort_sprite(t_main *lst, t_sprpos *pos)
{
	int			i;
	int			j;
	int			idx;
	t_sprpos	tmp;
	
	i = 0;
	while (i < lst->par.spr_num - 1)
	{
		idx = i;
		j = i + 1;
		while (j < lst->par.spr_num)
		{
			if (pos[idx].dist < pos[j].dist)
			{
				tmp = pos[idx];
				pos[idx] = pos[j];
				pos[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void		set_distance(t_main *lst, t_sprpos *pos)
{
	int			i;
	
	i = 0;
	while (i < lst->par.spr_num)
	{
		pos[i].dist = ((lst->posX - pos[i].x) * (lst->posX - pos[i].x)
			+ (lst->posY - pos[i].y) * (lst->posY - pos[i].y));
		i++;
	}
	sort_sprite(lst, pos);
}

static void	print_sprite(t_main *lst, t_spr *spr)
{
	while (spr->stripe < spr->drawEndX)
	{
		spr->texX = (int)((256 * (spr->stripe - (-spr->spriteW / 2 + spr->ScreenX))
			* textureW / spr->spriteW) / 256);
		if (spr->transY > 0 && spr->stripe > 0 && spr->stripe < lst->par.screenW &&
			spr->transY < lst->ray.zbuf[spr->stripe])
		{
			spr->y = spr->drawStartY;
			while (spr->y < spr->drawEndY)
			{
				spr->d = (spr->y) * 256 - lst->par.screenH * 128 + spr->spriteH * 128;
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

void			sprite(t_main *lst)
{
	t_spr	spr;	
	int		i;

	set_distance(lst, lst->par.sprpos);
	
	i = 0;
	while (i < lst->par.spr_num)
	{
		set_spr(lst, &spr, i);
		if (spr.drawStartY < 0)
			spr.drawStartY = 0;
		if (spr.drawEndY >= lst->par.screenH)
			spr.drawEndY = lst->par.screenH - 1;
		if (spr.drawStartX < 0)
			spr.drawStartX = 0;
		if (spr.drawEndX >= lst->par.screenW)
			spr.drawEndX = lst->par.screenW - 1;
		print_sprite(lst, &spr);
		i++;
	}
}
