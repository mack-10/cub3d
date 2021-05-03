/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:35:16 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/03 23:00:51 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check(t_main *lst, int argc, char *argv[])
{
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		error();
	lst->bmp_sign = 0;
	if (argc == 3)
	{
		if (!ft_strncmp(argv[2], "--save", ft_strlen(argv[2])))
			lst->bmp_sign = 1;
	}
}