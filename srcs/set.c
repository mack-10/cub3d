/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 21:13:08 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/03 02:17:02 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_lst(t_main *lst)
{
	lst->mlx = mlx_init();
	lst->posX = 0.0;
	lst->posY = 0.0;
	lst->dirX = -1.0;
	lst->dirY = 0.0;
	lst->planeX = 0.0;
	lst->planeY = 0.66;
	lst->moveSpeed = 0.3;
	lst->rotSpeed = 0.3;
}

void	set_ray(t_main *lst, int x)
{
	lst->ray.cameraX = 2 * x / (double)lst->par.screenW - 1;
	lst->ray.rayDirX = lst->dirX + lst->planeX * lst->ray.cameraX;
	lst->ray.rayDirY = lst->dirY + lst->planeY * lst->ray.cameraX;
	lst->ray.mapX = (int)(lst->posX);
	lst->ray.mapY = (int)(lst->posY);
	lst->ray.deltaDistX = fabs(1 / lst->ray.rayDirX);
	lst->ray.deltaDistY = fabs(1 / lst->ray.rayDirY);
	lst->ray.hit = 0;
}

void	set_buf(t_main *lst)
{
	int i; 
	int j;

	lst->ray.buf = (int **)ft_calloc(lst->par.screenH, sizeof(int *));
	i = 0;
	while (i < lst->par.screenH)
		lst->ray.buf[i++] = (int *)ft_calloc(lst->par.screenW, sizeof(int));
	i = 0;
	while (i < lst->par.screenH)
	{
		j = 0;
		while (j < lst->par.screenW)
			lst->ray.buf[i][j++] = 0;
		i++;
	}
	lst->ray.buf[i] = 0;

	lst->ray.zbuf = (double *)ft_calloc(lst->par.screenW, sizeof(double));
	i = 0;
	while (i < lst->par.screenW)
		lst->ray.zbuf[i++] = 0;
}
