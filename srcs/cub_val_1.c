/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_val_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 16:27:01 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/07 14:35:06 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	tex_path(t_par *par, char **split)
{
	if (!ft_strncmp(split[0], "NO", ft_strlen(split[0])))
	{
		par->tex_path[0] = ft_strdup(split[1]);
		par->sign_val[3] = 1;
	}
	else if (!ft_strncmp(split[0], "SO", ft_strlen(split[0]))
		&& !par->sign_val[4])
	{
		par->tex_path[1] = ft_strdup(split[1]);
		par->sign_val[4] = 1;
	}
	else if (!ft_strncmp(split[0], "WE", ft_strlen(split[0])))
	{
		par->tex_path[2] = ft_strdup(split[1]);
		par->sign_val[5] = 1;
	}
	else if (!ft_strncmp(split[0], "EA", ft_strlen(split[0])))
	{
		par->tex_path[3] = ft_strdup(split[1]);
		par->sign_val[6] = 1;
	}
	else if (!ft_strncmp(split[0], "S", ft_strlen(split[0])))
	{
		par->s_path = ft_strdup(split[1]);
		par->sign_val[7] = 1;
	}
}

static void	get_value(t_main *lst, t_par *par, char **split)
{
	if (check_val(split))
	{
		if (!ft_strncmp(split[0], "R", ft_strlen(split[0])))
			screen_size(lst, split);
		else if (!ft_strncmp(split[0], "F", ft_strlen(split[0])))
		{
			par->f_rgb = ft_strdup(split[1]);
			par->f_color = rgb_hex(lst->par.f_rgb);
			par->sign_val[1] = 1;
		}
		else if (!ft_strncmp(split[0], "C", ft_strlen(split[0])))
		{
			par->c_rgb = ft_strdup(split[1]);
			par->c_color = rgb_hex(lst->par.c_rgb);
			par->sign_val[2] = 1;
		}
		else
			tex_path(par, split);
	}
	else
	{
		free_double(split);
		error();
	}
}

static void	search_letter(t_main *lst, t_par *par, char *src)
{
	char	**split;
	char	*tmp;

	if ((src[0] >= '0' && src[0] <= '2') || src[0] == ' ')
		lst->par.sign_map = 1;
	if (lst->par.sign_map)
	{
		if (!src[0])
			error();
		tmp = g_strjoin(par->map_one, src);
		free_one(par->map_one);
		par->map_one = g_strjoin(tmp, "\n");
		free_one(tmp);
	}
	if (src[0] && !lst->par.sign_map)
	{
		split = ft_split(src, ' ');
		get_value(lst, par, split);
		par->cnt_val++;
		free_double(split);
	}
	free_one(src);
}

void		cub_val(t_main *lst, char *file)
{
	char	*src;
	int		fd;
	int		i;

	mlx_get_screen_size(lst->mlx, &lst->max_w, &lst->max_h);
	fd = open(file, O_RDONLY);
	lst->par.cnt_val = 0;
	lst->par.sign_map = 0;
	lst->par.map_one = g_strjoin("", "");
	i = -1;
	while (++i < 8)
		lst->par.sign_val[i] = 0;
	while (get_next_line(fd, &src))
		search_letter(lst, &lst->par, src);
	search_letter(lst, &lst->par, src);
	close(fd);
	i = -1;
	while (++i < 8)
	{
		if (!lst->par.sign_val[i])
			error();
	}
	if (lst->par.cnt_val != 8)
		error();
	map(lst, &lst->par);
}
