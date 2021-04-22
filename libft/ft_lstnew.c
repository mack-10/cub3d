/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:18:30 by sujeon            #+#    #+#             */
/*   Updated: 2020/11/04 08:55:10 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *new_node;

	if (!(new_node = malloc(sizeof(t_list))))
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
