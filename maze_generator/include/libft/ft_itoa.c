/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:00:10 by acronert          #+#    #+#             */
/*   Updated: 2023/11/08 16:36:53 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlength(int n)
{
	long	i;
	int		len;

	i = 1;
	len = 0;
	if (n <= 0)
	{
		len++;
		n = -n;
	}
	while (n / i)
	{
		i *= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		nlen;
	long	nbr;

	nbr = n;
	nlen = ft_intlength(nbr);
	ptr = malloc((nlen + 1) * sizeof(char));
	if (!ptr)
		return (0);
	ptr[nlen] = '\0';
	if (nbr < 0)
		nbr = -nbr;
	while (nlen > 0)
	{
		ptr[nlen - 1] = (nbr % 10) + '0';
		nlen--;
		nbr /= 10;
	}
	if (ptr[0] == '0' && ptr[1])
		ptr[0] = '-';
	return (ptr);
}
