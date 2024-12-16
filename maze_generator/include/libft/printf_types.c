/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:09 by acronert          #+#    #+#             */
/*   Updated: 2024/01/12 15:22:22 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_dec(int fd, int n)
{
	return (ft_put_longint(fd, n, 0));
}

int	ft_print_int(int fd, int n)
{
	return (ft_put_longint(fd, n, 0));
}

int	ft_print_udec(int fd, unsigned int n)
{
	return (ft_put_longint(fd, n, 0));
}

int	ft_print_lowhex(int fd, unsigned int n)
{
	return (ft_put_ulongint(fd, n, LHEX_BASE, 0));
}

int	ft_print_upphex(int fd, unsigned int n)
{
	return (ft_put_ulongint(fd, n, UHEX_BASE, 0));
}
