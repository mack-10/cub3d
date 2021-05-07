/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 02:25:03 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/07 14:43:04 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_all(t_main *lst)
{
	int i;

	i = 0;
	while (i < lst->par.screenH)
	{
		free(lst->ray.buf[i]);
		lst->ray.buf[i] = 0;
		i++;
	}
	free(lst->ray.buf);
	lst->ray.buf = 0;
	free(lst->ray.zbuf);
	lst->ray.zbuf = 0;
}

int			main_loop(t_main *lst)
{
	raycasting(lst);
	sprite(lst);
	draw(lst);
	free_all(lst);
	return (0);
}
