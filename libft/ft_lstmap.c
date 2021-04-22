/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:31:43 by sujeon            #+#    #+#             */
/*   Updated: 2020/11/04 09:42:45 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*node;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	if (!(new_lst = ft_lstnew(f(lst->content))))
		ft_lstdelone(new_lst, del);
	tmp = new_lst;
	while (lst->next)
	{
		if (!(node = ft_lstnew(f(lst->content))))
			ft_lstclear(&new_lst, del);
		new_lst->next = node;
		lst = lst->next;
		new_lst = new_lst->next;
	}
	return (tmp);
}
