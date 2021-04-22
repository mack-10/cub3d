/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 21:23:56 by sujeon            #+#    #+#             */
/*   Updated: 2020/11/04 23:28:32 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t idx1;
	size_t idx2;

	idx1 = 0;
	if (!*needle)
		return ((char *)haystack);
	while (idx1 < len && haystack[idx1])
	{
		idx2 = 0;
		if (haystack[idx1] == needle[idx2])
		{
			while (idx1 + idx2 < len && haystack[idx1 + idx2] == needle[idx2]
					&& needle[idx2])
				idx2++;
			if (!needle[idx2])
				return ((char *)haystack + idx1);
		}
		idx1++;
	}
	return (NULL);
}
