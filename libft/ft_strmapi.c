/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 22:53:13 by sujeon            #+#    #+#             */
/*   Updated: 2020/11/03 14:34:15 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	int		idx;

	idx = 0;
	if (!s)
		return (NULL);
	if (!(new_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[idx])
	{
		new_str[idx] = f(idx, s[idx]);
		idx++;
	}
	new_str[idx] = 0;
	return (new_str);
}
