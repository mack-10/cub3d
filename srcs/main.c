/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:37:47 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/03 02:26:48 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 			error()
{
	printf("Error\n");
	exit(0);
}

static int		ft_exit()
{
	exit(0);
	return (0);
}

int				main(int argc, char *argv[])
{
	t_main	lst;

	if (argc == 2)
	{
		if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
			error();
		set_lst(&lst);
		parsing(&lst, argv[1]);
		load_texture(&lst);
		lst.win = mlx_new_window(lst.mlx, lst.par.screenW, lst.par.screenH, "cub3D");
		lst.img.img = mlx_new_image(lst.mlx, lst.par.screenW, lst.par.screenH);
		lst.img.data = (int *)mlx_get_data_addr(lst.img.img, &lst.img.bpp, &lst.img.size_l, &lst.img.endian);
		mlx_loop_hook(lst.mlx, &main_loop, &lst);
		mlx_hook(lst.win, X_EVENT_KEY_PRESS, 0, &key_press, &lst);
		mlx_hook(lst.win, X_EVENT_KEY_EXIT, 0, &ft_exit, &lst);
		mlx_loop(lst.mlx);
	}
	else
		error();
	while (1)
		;
}
