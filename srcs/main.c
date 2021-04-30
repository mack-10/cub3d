/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:37:47 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/01 03:52:01 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 		error(void)
{
	printf("Error\n");
	exit(0);
}

int			main(int argc, char *argv[])
{
	t_main	lst;
	int		fd;

	if (argc == 2)
	{
		set_lst(&lst);
		fd = open(argv[1], O_RDONLY);
		parsing(&lst, fd);
		load_texture(&lst);
		lst.win = mlx_new_window(lst.mlx, lst.par.screenW, lst.par.screenH, "cub3D");
		lst.img.img = mlx_new_image(lst.mlx, lst.par.screenW, lst.par.screenH);
		lst.img.data = (int *)mlx_get_data_addr(lst.img.img, &lst.img.bpp, &lst.img.size_l, &lst.img.endian);
		mlx_loop_hook(lst.mlx, &ray_c, &lst);
		mlx_hook(lst.win, X_EVENT_KEY_PRESS, 0, &key_press, &lst);
		mlx_loop(lst.mlx);
	}
	else
		printf("Error\n");
	while (1)
		;
}
