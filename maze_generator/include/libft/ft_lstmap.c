/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:28:40 by acronert          #+#    #+#             */
/*   Updated: 2023/11/14 09:29:50 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*current;

	if (!lst || !f || !del)
		return (NULL);
	start = NULL;
	while (lst)
	{
		current = ft_lstnew((*f)(lst->content));
		if (!current)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		ft_lstadd_back(&start, current);
		lst = lst->next;
	}
	return (start);
}
