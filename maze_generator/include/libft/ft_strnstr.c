/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:25:13 by acronert          #+#    #+#             */
/*   Updated: 2023/11/13 13:10:28 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *big, const char *little, size_t size)
{
	size_t	i;
	size_t	j;

	if (!little[0] || big == little)
		return ((char *)big);
	if (!size)
		return (NULL);
	i = 0;
	while (big[i] && i < size)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j < size) && little[j])
			j++;
		if (!little[j])
			return (&((char *)big)[i]);
		i++;
	}
	return (NULL);
}
