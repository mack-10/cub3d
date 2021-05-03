/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:37:47 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/04 00:41:42 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 		error()
{
	printf("Error\n");
	exit(0);
}

int			ft_exit()
{
	exit(0);
	return (0);
}

int			main(int argc, char *argv[])
{
	t_main	lst;

	if (argc >= 2)
	{
		check(&lst, argc, argv);
		set_lst(&lst);
		parsing(&lst, argv[1]);
		load_texture(&lst);
		if (lst.bmp_sign)
			bmp(&lst);
		else
		{
			lst.win = mlx_new_window(lst.mlx, lst.par.screenW, lst.par.screenH, "cub3D");
			lst.img.img = mlx_new_image(lst.mlx, lst.par.screenW, lst.par.screenH);
			lst.img.data = (int *)mlx_get_data_addr(lst.img.img, &lst.img.bpp, &lst.img.size_l, &lst.img.endian);
			mlx_loop_hook(lst.mlx, &main_loop, &lst);
			mlx_hook(lst.win, X_EVENT_KEY_PRESS, 0, &key_press, &lst);
			mlx_hook(lst.win, X_EVENT_KEY_EXIT, 0, &ft_exit, 0);
			mlx_loop(lst.mlx);
		}
			// mlx(&lst);
	}
	else
		error();
	return (0);
}
