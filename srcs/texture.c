/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:32:07 by sujeon            #+#    #+#             */
/*   Updated: 2021/04/18 17:32:16 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		load_image(t_val *lst, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(lst->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(lst->mlx, img->img);
}

void			load_texture(t_val *lst)
{
	t_img	img;

	load_image(lst, lst->texture[0], "textures/eagle.xpm", &img);
	load_image(lst, lst->texture[1], "textures/redbrick.xpm", &img);
	load_image(lst, lst->texture[2], "textures/purplestone.xpm", &img);
	load_image(lst, lst->texture[3], "textures/greystone.xpm", &img);
	load_image(lst, lst->texture[4], "textures/bluestone.xpm", &img);
	load_image(lst, lst->texture[5], "textures/mossy.xpm", &img);
	load_image(lst, lst->texture[6], "textures/wood.xpm", &img);
	load_image(lst, lst->texture[7], "textures/colorstone.xpm", &img);
}