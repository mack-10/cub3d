/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:32:07 by sujeon            #+#    #+#             */
/*   Updated: 2021/04/25 19:14:54 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		load_image(t_val *lst, int *texture, char *path, t_img *img)
{
	int x;
	int y;

	img->img = mlx_xpm_file_to_image(
		lst->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(
		img->img, &img->bpp, &img->size_l, &img->endian);
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(lst->mlx, img->img);
}

void			load_texture(t_val *lst)
{
	t_img	img;
	int		i;

	i = 0;
	while (i < 4)
	{
		load_image(lst, lst->texture[i], lst->tex_path[i], &img);
		i++;
	}		
}
