/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:35:00 by acronert          #+#    #+#             */
/*   Updated: 2023/11/08 13:53:12 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	val;
	int	neg;

	i = 0;
	val = 0;
	neg = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		val = (10 * val) + (str[i] - '0');
		i++;
	}
	return (neg * val);
}
/*
#include <stdio.h>
int	main (void)
{
	printf ("val = %d\n", ft_atoi("123456"));
	printf ("val = %d\n", ft_atoi("-123456"));
	printf ("val = %d\n", ft_atoi("gfdgfsd-123456"));
	printf ("val = %d\n", ft_atoi("123456gfdg"));
	printf ("val = %d\n", ft_atoi("123ff456"));
}
*/
