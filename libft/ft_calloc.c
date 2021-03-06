/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 21:02:22 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/01 22:42:01 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/cub3d.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *p;

	if (!(p = malloc(nmemb * size)))
		error();
	ft_bzero(p, nmemb * size);
	return (p);
}
