/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 21:13:08 by sujeon            #+#    #+#             */
/*   Updated: 2021/04/25 21:20:24 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_ray(t_val *lst, t_ray *ray, int x)
{
	ray->cameraX = 2 * x / (double)lst->screenW - 1;
	ray->rayDirX = lst->dirX + lst->planeX * ray->cameraX;
	ray->rayDirY = lst->dirY + lst->planeY * ray->cameraX;
	ray->mapX = (int)(lst->posX);
	ray->mapY = (int)(lst->posY);
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->hit = 0;
}

void	set_lst(t_val *lst)
{
	lst->mlx = mlx_init();
	lst->posX = 22.0;
	lst->posY = 11.5;
	lst->dirX = -1.0;
	lst->dirY = 0.0;
	lst->planeX = 0.0;
	lst->planeY = 0.66;
	lst->moveSpeed = 0.3;
	lst->rotSpeed = 0.3;
}

void	set_buf(t_val *lst)
{
	int i; 
	int j;

	if (!(lst->buf = (int **)malloc(sizeof(int *) * lst->screenH + 1)))
		error();
	i = 0;
	while (i < lst->screenH)
	{
		if (!(lst->buf[i] = (int *)malloc(sizeof(int) * lst->screenW)))
			error();
		i++;
	}
	i = 0;
	while (i < lst->screenH)
	{
		j = 0;
		while (j < lst->screenW)
			lst->buf[i][j++] = 0;
		i++;
	} 
}