/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:37:36 by acronert          #+#    #+#             */
/*   Updated: 2024/01/15 09:39:04 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_three(char const *a, char const *b, char const *c)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *)malloc((ft_strlen(a) + ft_strlen(b) + ft_strlen(c) + 1)
			* sizeof(char));
	if (!res)
		return (NULL);
	while (a[i++])
		res[i - 1] = a[i - 1];
	i = 0;
	while (b[i])
	{
		res[i + ft_strlen(a)] = b[i];
		i++;
	}
	i = 0;
	while (c[i])
	{
		res[i + ft_strlen(a) + ft_strlen(b)] = c[i];
		i++;
	}
	res[ft_strlen(a) + ft_strlen(b) + ft_strlen(c)] = '\0';
	return (res);
}
