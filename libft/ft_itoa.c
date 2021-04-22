/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 20:40:36 by sujeon            #+#    #+#             */
/*   Updated: 2020/11/04 11:01:20 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*n_positive(int n)
{
	char	*str;
	int		cpy_n;
	int		idx;

	cpy_n = n;
	idx = 0;
	while (cpy_n)
	{
		cpy_n = cpy_n / 10;
		idx++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (idx + 1))))
		return (0);
	str[idx] = 0;
	while (--idx != -1)
	{
		str[idx] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}

char	*n_negative(int n)
{
	char	*str;
	int		cpy_n;
	int		idx;

	cpy_n = n;
	idx = 1;
	while (cpy_n)
	{
		cpy_n = cpy_n / 10;
		idx++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (idx + 1))))
		return (0);
	str[0] = '-';
	str[idx] = 0;
	while (--idx != 0)
	{
		str[idx] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	if (!n)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n > 0)
		return (n_positive(n));
	else
	{
		n *= -1;
		return (n_negative(n));
	}
}
