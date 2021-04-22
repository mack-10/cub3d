/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:13:59 by sujeon            #+#    #+#             */
/*   Updated: 2020/11/08 15:53:12 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		search_begin(char *str, char const *set)
{
	int cnt;
	int idx1;
	int idx2;

	cnt = 0;
	idx1 = 0;
	while (str[idx1])
	{
		idx2 = 0;
		while (set[idx2])
		{
			if (str[idx1] == set[idx2])
			{
				cnt++;
				break ;
			}
			idx2++;
		}
		if (!set[idx2])
			break ;
		idx1++;
	}
	return (cnt);
}

int		search_end(char *str, char const *set)
{
	int cnt;
	int end;
	int idx;

	end = ft_strlen(str) - 1;
	cnt = 0;
	while (end >= 0)
	{
		idx = 0;
		while (set[idx])
		{
			if (str[end] == set[idx])
			{
				cnt++;
				break ;
			}
			idx++;
		}
		if (!set[idx])
			break ;
		end--;
	}
	return (cnt);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*cpy_s1;
	char	*trim;
	int		cnt_b;
	int		cnt_e;
	int		total;

	if (!s1 || !set)
		return (NULL);
	cpy_s1 = (char *)s1;
	cnt_b = search_begin(cpy_s1, set);
	if (cnt_b == (int)ft_strlen(s1))
		return (ft_strdup(""));
	cnt_e = search_end(cpy_s1 + cnt_b, set);
	total = cnt_b + cnt_e;
	if (!(trim = ft_substr(cpy_s1, cnt_b, ft_strlen(cpy_s1) - total)))
		return (NULL);
	return (trim);
}
