/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:35:45 by acronert          #+#    #+#             */
/*   Updated: 2024/01/18 18:14:32 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_ulongint(int fd, unsigned long int n, char *base, int len)
{
	unsigned int	base_len;

	base_len = ft_strlen_int(base);
	if (n < base_len)
	{
		len += write(fd, &base[n], 1);
		return (len);
	}
	else
	{
		len = ft_put_ulongint(fd, n / base_len, base, len);
		return (ft_put_ulongint(fd, n % base_len, base, len));
	}
}

int	ft_put_longint(int fd, long int n, int len)
{
	if (n < 0)
	{
		len += ft_print_char(fd, '-');
		n = -n;
	}
	if (n < 10)
	{
		len += ft_print_char(fd, n + '0');
		return (len);
	}
	else
	{
		len = ft_put_longint(fd, n / 10, len);
		return (ft_put_longint(fd, n % 10, len));
	}
}

int	ft_strlen_int(char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
		return (0);
	while (str[len])
		len++;
	return (len);
}
