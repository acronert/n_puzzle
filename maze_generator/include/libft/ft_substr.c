/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:29:17 by acronert          #+#    #+#             */
/*   Updated: 2023/11/13 10:16:44 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	real_len;
	size_t	i;

	real_len = len;
	if (start + len > ft_strlen(s) && start < ft_strlen(s))
		real_len = ft_strlen(s) - start;
	else if (start >= ft_strlen(s))
		real_len = 0;
	sub = malloc((real_len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < real_len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
