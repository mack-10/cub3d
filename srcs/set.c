/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 21:13:08 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/07 15:17:24 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx(t_main *lst)
{
	lst->win = mlx_new_window(lst->mlx, lst->par.screen_w, lst->par.screen_h,
		"cub3D");
	lst->img.img = mlx_new_image(lst->mlx, lst->par.screen_w,
		lst->par.screen_h);
	lst->img.data = (int *)mlx_get_data_addr(lst->img.img, &lst->img.bpp,
		&lst->img.size_l, &lst->img.endian);
	mlx_loop_hook(lst->mlx, &main_loop, lst);
	mlx_hook(lst->win, X_EVENT_KEY_PRESS, 0, &key_press, lst);
	mlx_hook(lst->win, X_EVENT_KEY_EXIT, 0, &ft_exit, 0);
	mlx_loop(lst->mlx);
}

void	set_lst(t_main *lst)
{
	lst->mlx = mlx_init();
	lst->pos_x = 0.5;
	lst->pos_y = 0.5;
	lst->dir_x = 0.0;
	lst->dir_y = 0.0;
	lst->plane_x = 0.0;
	lst->plane_y = 0.0;
	lst->movespeed = 0.5;
	lst->rotspeed = 0.2;
}

void	set_map(t_main *lst, t_par *par)
{
	int i;

	par->map = (int **)ft_calloc(par->map_h, sizeof(int *));
	i = 0;
	while (i < par->map_h)
	{
		par->map[i] = (int *)ft_calloc(par->map_w[i], sizeof(int));
		i++;
	}
	lst->par.sprpos = (t_sprpos *)ft_calloc(lst->par.spr_num, sizeof(t_sprpos));
}

void	set_ray(t_main *lst, int x)
{
	lst->ray.camerax = 2 * x / (double)lst->par.screen_w - 1;
	lst->ray.raydir_x = lst->dir_x + lst->plane_x * lst->ray.camerax;
	lst->ray.raydir_y = lst->dir_y + lst->plane_y * lst->ray.camerax;
	lst->ray.map_x = (int)(lst->pos_x);
	lst->ray.map_y = (int)(lst->pos_y);
	lst->ray.deltadist_x = fabs(1 / lst->ray.raydir_x);
	lst->ray.deltadist_y = fabs(1 / lst->ray.raydir_y);
	lst->ray.hit = 0;
}

void	set_buf(t_main *lst)
{
	int i;
	int	j;

	lst->ray.buf = (int **)ft_calloc(lst->par.screen_h, sizeof(int *));
	i = 0;
	while (i < lst->par.screen_h)
		lst->ray.buf[i++] = (int *)ft_calloc(lst->par.screen_w, sizeof(int));
	i = 0;
	while (i < lst->par.screen_h)
	{
		j = 0;
		while (j < lst->par.screen_w)
			lst->ray.buf[i][j++] = 0;
		i++;
	}
	lst->ray.buf[i] = 0;
	lst->ray.zbuf = (double *)ft_calloc(lst->par.screen_w, sizeof(double));
	i = 0;
	while (i < lst->par.screen_w)
		lst->ray.zbuf[i++] = 0;
}
