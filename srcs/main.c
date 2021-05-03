/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:37:47 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/04 00:48:30 by sujeon           ###   ########.fr       */
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
			mlx(&lst);
	}
	else
		error();
	return (0);
}
