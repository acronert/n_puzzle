/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:19:57 by acronert          #+#    #+#             */
/*   Updated: 2024/01/12 14:04:16 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		len;

	len = ft_strlen(s);
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	ft_strcpy(dup, (char *)s);
	return (dup);
}
