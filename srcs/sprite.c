/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 03:49:55 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/07 15:18:27 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_spr(t_main *lst, t_spr *spr, int i)
{
	t_sprpos	*pos;

	pos = lst->par.sprpos;
	spr->spr_x = pos[i].x - lst->pos_x;
	spr->spr_y = pos[i].y - lst->pos_y;
	spr->invdet = 1.0 / (lst->plane_x * lst->dir_y - lst->dir_x * lst->plane_y);
	spr->trans_x = spr->invdet * (lst->dir_y * spr->spr_x - lst->dir_x
		* spr->spr_y);
	spr->trans_y = spr->invdet * (-lst->plane_y * spr->spr_x + lst->plane_x
		* spr->spr_y);
	spr->screenx = (int)((lst->par.screen_w / 2) *
		(1 + spr->trans_x / spr->trans_y));
	spr->spr_h = (int)fabs(lst->par.screen_h / spr->trans_y);
	spr->spr_w = (int)fabs(lst->par.screen_h / spr->trans_y);
	spr->drawstart_x = -spr->spr_w / 2 + spr->screenx;
	spr->drawstart_y = -spr->spr_h / 2 + lst->par.screen_h / 2;
	spr->drawend_x = spr->spr_w / 2 + spr->screenx;
	spr->drawend_y = spr->spr_h / 2 + lst->par.screen_h / 2;
	spr->stripe = spr->drawstart_x;
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

static void	set_distance(t_main *lst, t_sprpos *pos)
{
	int			i;

	i = 0;
	while (i < lst->par.spr_num)
	{
		pos[i].dist = ((lst->pos_x - pos[i].x) * (lst->pos_x - pos[i].x)
			+ (lst->pos_y - pos[i].y) * (lst->pos_y - pos[i].y));
		i++;
	}
	sort_sprite(lst, pos);
}

static void	print_sprite(t_main *lst, t_spr *spr)
{
	while (spr->stripe < spr->drawend_x)
	{
		spr->tex_x = (int)((256 * (spr->stripe - (-spr->spr_w / 2 +
			spr->screenx)) * TEXTUREW / spr->spr_w) / 256);
		if (spr->trans_y > 0 && spr->stripe > 0 &&
			spr->stripe < lst->par.screen_w &&
			spr->trans_y < lst->ray.zbuf[spr->stripe])
		{
			spr->y = spr->drawstart_y;
			while (spr->y < spr->drawend_y)
			{
				spr->d = (spr->y) * 256 - lst->par.screen_h * 128 +
					spr->spr_h * 128;
				spr->tex_y = ((spr->d * TEXTUREW) / spr->spr_h) / 256;
				spr->color = lst->tex.texture[4]
					[TEXTUREW * spr->tex_y + spr->tex_x];
				if (spr->color & 0x00FFFFFF)
					lst->ray.buf[spr->y][spr->stripe] = spr->color;
				spr->y++;
			}
		}
		spr->stripe++;
	}
}

void		sprite(t_main *lst)
{
	t_spr	spr;
	int		i;

	set_distance(lst, lst->par.sprpos);
	i = 0;
	while (i < lst->par.spr_num)
	{
		set_spr(lst, &spr, i);
		if (spr.drawstart_y < 0)
			spr.drawstart_y = 0;
		if (spr.drawend_y >= lst->par.screen_h)
			spr.drawend_y = lst->par.screen_h - 1;
		if (spr.drawstart_x < 0)
			spr.drawstart_x = 0;
		if (spr.drawend_x >= lst->par.screen_w)
			spr.drawend_x = lst->par.screen_w - 1;
		print_sprite(lst, &spr);
		i++;
	}
}
