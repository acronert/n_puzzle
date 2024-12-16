/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_strsep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:28:24 by acronert          #+#    #+#             */
/*   Updated: 2024/01/18 18:28:42 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_strsep(char *str, char **strsep)
{
	int	i;

	i = 0;
	while (strsep[i])
	{
		if (!ft_strncmp(str, strsep[i], ft_strlen(strsep[i]) + 1))
			return (1);
		i++;
	}
	return (0);
}
