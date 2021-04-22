/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 00:54:28 by sujeon            #+#    #+#             */
/*   Updated: 2020/11/04 10:20:11 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int idx;
	int n;
	int sign;

	idx = 0;
	n = 0;
	sign = 1;
	while (str[idx] == ' ' || str[idx] == '\n' || str[idx] == '\t' ||
			str[idx] == '\r' || str[idx] == '\v' || str[idx] == '\f')
		idx++;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			sign = -1;
		idx++;
	}
	while (str[idx] >= '0' && str[idx] <= '9')
	{
		n = (10 * n) + (str[idx] - '0');
		idx++;
	}
	return (sign * n);
}
