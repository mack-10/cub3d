/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 21:12:18 by sujeon            #+#    #+#             */
/*   Updated: 2020/11/02 11:22:31 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp_s;
	int		cnt;

	cnt = ft_strlen(s);
	tmp_s = (char *)s + cnt;
	if (*tmp_s == (char)c)
		return (tmp_s);
	tmp_s--;
	while (cnt--)
	{
		if (*tmp_s == (char)c)
			return (tmp_s);
		tmp_s--;
	}
	return (0);
}
