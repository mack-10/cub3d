/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:37:47 by sujeon            #+#    #+#             */
/*   Updated: 2021/04/18 17:37:49 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_val lst;
	lst.mlx = mlx_init();

	lst.posX = 22.0;
	lst.posY = 11.5;
	lst.dirX = -1.0;
	lst.dirY = 0.0;
	lst.planeX = 0.0;
	lst.planeY = 0.66;

	for (int i = 0; i < screenH; i++)
	{
		for (int j = 0; j < screenW; j++)
		{
			lst.buf[i][j] = 0;
		}
	}

	if (!(lst.texture = (int **)malloc(sizeof(int *) * 8)))
		return (-1);
	for (int i = 0; i < 8; i++)
	{
		if (!(lst.texture[i] = (int *)malloc(sizeof(int) * (textureH * textureW))))
			return (-1);
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < textureH * textureW; j++)
		{
			lst.texture[i][j] = 0;
		}
	}

	load_texture(&lst);

	lst.moveSpeed = 0.05;
	lst.rotSpeed = 0.05;
	
	lst.win = mlx_new_window(lst.mlx, screenW, screenH, "mlx");

	lst.img.img = mlx_new_image(lst.mlx, screenW, screenH);
	lst.img.data = (int *)mlx_get_data_addr(lst.img.img, &lst.img.bpp, &lst.img.size_l, &lst.img.endian);

	mlx_loop_hook(lst.mlx, &ray_c, &lst);
	mlx_hook(lst.win, X_EVENT_KEY_PRESS, 0, &key_press, &lst);

	mlx_loop(lst.mlx);
}