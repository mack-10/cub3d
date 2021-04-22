/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 18:03:28 by sujeon            #+#    #+#             */
/*   Updated: 2020/11/03 10:44:35 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			idx;
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	idx = 0;
	tmp_s1 = (unsigned char *)s1;
	tmp_s2 = (unsigned char *)s2;
	while (n-- && (tmp_s1[idx] || tmp_s2[idx]))
	{
		if (tmp_s1[idx] != tmp_s2[idx])
			return (tmp_s1[idx] - tmp_s2[idx]);
		idx++;
	}
	return (0);
}
