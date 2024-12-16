/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:37:09 by acronert          #+#    #+#             */
/*   Updated: 2023/11/13 09:47:21 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*ptr;

	if (!lst)
		return (0);
	ptr = lst;
	count = 1;
	while (ptr->next != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}
