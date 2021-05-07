/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:35:16 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/07 14:38:16 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_str(char *src, char *str)
{
	int i;
	int j;

	i = -1;
	while (src[++i])
	{
		if (src[i] == str[0])
		{
			j = -1;
			while (str[++j])
			{
				if (src[i + j] != str[j])
					break ;
			}
			if (!str[j])
			{
				if (src[i + j])
					break ;
				else
					return (1);
			}
		}
	}
	return (0);
}

void		check(t_main *lst, int argc, char *argv[])
{
	if (!check_str(argv[1], ".cub"))
		error();
	lst->bmp_sign = 0;
	if (argc == 3)
	{
		if (!check_str(argv[2], "--save"))
			error();
		else
			lst->bmp_sign = 1;
	}
}
