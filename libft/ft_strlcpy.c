/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 18:11:23 by sujeon            #+#    #+#             */
/*   Updated: 2020/11/04 10:20:41 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		idx;
	size_t		src_len;

	if (!src)
		return (0);
	src_len = ft_strlen(src);
	idx = 0;
	if (!size || !src)
		return (src_len);
	while (idx + 1 < size && src[idx])
	{
		dst[idx] = src[idx];
		idx++;
	}
	dst[idx] = 0;
	return (src_len);
}
