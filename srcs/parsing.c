/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 16:27:01 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/02 04:36:23 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	tex_path(t_par *par, char **split)
{
	if (!ft_strncmp(split[0], "NO", 2))
		par->tex_path[0] = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "SO", 2))
		par->tex_path[1] = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "WE", 2))
		par->tex_path[2] = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "EA", 2))
		par->tex_path[3] = ft_strdup(split[1]);
	else
		par->s_path = ft_strdup(split[1]);
}

static void	get_value(t_par *par, char **split)
{
	if (check_val(split))
	{
		if (!ft_strncmp(split[0], "R", 1))
		{
			par->screenW = ft_atoi(split[1]);
			par->screenH = ft_atoi(split[2]);
		}
		else if (!ft_strncmp(split[0], "F", 1))
			par->f_rgb = ft_strdup(split[1]);
		else if (!ft_strncmp(split[0], "C", 1))
			par->c_rgb = ft_strdup(split[1]);
		else
			tex_path(par, split);
	}
	else
	{
		free_double(split);
		error();
	}
}

static void	get_val_cub(t_par *par, char *src)
{
	char	**split;
	char	*tmp;
	
	if (src[0] == '1' || src[0] == ' ')
	{
		tmp = g_strjoin(par->map_one, src);
		free_one(par->map_one);
		par->map_one = g_strjoin(tmp, "\n");
		free_one(tmp);
	}
	else if (src[0] >= 'A')
	{
		split = ft_split(src, ' ');
		get_value(par, split);
		par->cnt_set++;
		free_double(split);
	}
	free_one(src);
}

void		parsing(t_main *lst, char *file)
{
	char	*src;
	int		fd;

	fd = open(file, O_RDONLY);
	lst->par.cnt_set = 0;
	lst->par.map_one = g_strjoin("", "");
	while (get_next_line(fd, &src))
		get_val_cub(&lst->par, src);
	get_val_cub(&lst->par, src);
	close(fd);
	split_map(lst, &lst->par);
	if (lst->par.cnt_set != 8)
		error();
}