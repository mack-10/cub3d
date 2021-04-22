/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 02:10:54 by sujeon            #+#    #+#             */
/*   Updated: 2020/11/03 09:25:07 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	tmp1 = (unsigned char *)dest;
	tmp2 = (unsigned char *)src;
	while (n--)
	{
		*tmp1 = *tmp2;
		if (*tmp1 == (unsigned char)c)
			return (tmp1 + 1);
		tmp1++;
		tmp2++;
	}
	return (NULL);
}
