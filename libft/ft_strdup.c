/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 21:38:39 by sujeon            #+#    #+#             */
/*   Updated: 2020/11/03 11:34:27 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	int		idx;
	char	*new_str;

	idx = 0;
	size = ft_strlen(s);
	if (!(new_str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (idx < size)
	{
		new_str[idx] = s[idx];
		idx++;
	}
	new_str[idx] = 0;
	return (new_str);
}
