/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 23:37:39 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/02 04:20:21 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_double(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		s[i++] = NULL;
	}		
	free(s);
	s = NULL;
}

void	free_one(char *s)
{
	free(s);
	s = NULL;
}

int		check_val(char **s)
{
	int	i;
	int n;
	
	if (!ft_strncmp(s[0], "R", ft_strlen(s[0])))
		n = 3;
	else
		n = 2;
	i = 0;
	while (s[i])
		i++;
	if (n != i)
		return (0);
	return (1);
}