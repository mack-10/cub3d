/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:37:47 by sujeon            #+#    #+#             */
/*   Updated: 2021/04/24 21:43:32 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int 		print_error(void)
{
	printf("Error\n");
	return (0);
}

int			main(int argc, char *argv[])
{
	t_val	lst;
	int		fd;

	lst.mlx = mlx_init();
	lst.posX = 22.0;
	lst.posY = 11.5;
	lst.dirX = -1.0;
	lst.dirY = 0.0;
	lst.planeX = 0.0;
	lst.planeY = 0.66;
	lst.moveSpeed = 0.3;
	lst.rotSpeed = 0.3;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (!parsing(&lst, fd))
			return(print_error());
		load_texture(&lst);
		lst.win = mlx_new_window(lst.mlx, screenW, screenH, "cub3D");
		lst.img.img = mlx_new_image(lst.mlx, screenW, screenH);
		lst.img.data = (int *)mlx_get_data_addr(lst.img.img, &lst.img.bpp, &lst.img.size_l, &lst.img.endian);
		mlx_loop_hook(lst.mlx, &ray_c, &lst);
		mlx_hook(lst.win, X_EVENT_KEY_PRESS, 0, &key_press, &lst);
		mlx_loop(lst.mlx);
	}
	else
		printf("Error\n");	
}