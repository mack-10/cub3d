/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:59:08 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/07 15:12:34 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

static void	bmp_header(t_main *lst, int fd, int padding)
{
	unsigned char	bmp_h[54];
	int				fd_size;
	int				i;

	fd_size = 54 + ((lst->par.screen_w * 3 + padding) * lst->par.screen_h);
	ft_memset(bmp_h, 0, 54);
	bmp_h[0] = (unsigned char)('B');
	bmp_h[1] = (unsigned char)('M');
	set_int_in_char(bmp_h + 2, fd_size);
	bmp_h[10] = (unsigned char)(54);
	bmp_h[14] = (unsigned char)(40);
	set_int_in_char(bmp_h + 18, lst->par.screen_w);
	set_int_in_char(bmp_h + 22, lst->par.screen_h);
	bmp_h[26] = (unsigned char)(1);
	bmp_h[28] = (unsigned char)(24);
	write(fd, bmp_h, 54);
}

static void	write_data(t_main *lst, int fd, int padding)
{
	unsigned char	zero[3];
	int				i;
	int				j;

	ft_memset(zero, 0, 3);
	i = lst->par.screen_h;
	while (--i >= 0)
	{
		j = 0;
		while (j < lst->par.screen_w)
		{
			write(fd, &lst->ray.buf[i][j], 3);
			j++;
		}
		write(fd, zero, padding);
	}
}

void		bmp(t_main *lst)
{
	int		fd;
	int		padding;

	raycasting(lst);
	sprite(lst);
	padding = (4 - ((lst->par.screen_w * 3) % 4)) % 4;
	if ((fd = open("save.bmp", O_WRONLY | O_CREAT | O_TRUNC, 00777)) < 0)
		error();
	bmp_header(lst, fd, padding);
	write_data(lst, fd, padding);
	close(fd);
	exit(0);
}
