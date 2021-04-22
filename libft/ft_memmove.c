/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 02:36:44 by sujeon            #+#    #+#             */
/*   Updated: 2020/11/03 09:26:04 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*tmp1;
	const unsigned char	*tmp2;

	tmp1 = (unsigned char *)dst;
	tmp2 = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (dst <= src)
	{
		i = 0;
		while (i < len)
		{
			*(tmp1 + i) = *(tmp2 + i);
			i++;
		}
	}
	else
	{
		while (len--)
			*(tmp1 + len) = *(tmp2 + len);
	}
	return (dst);
}
