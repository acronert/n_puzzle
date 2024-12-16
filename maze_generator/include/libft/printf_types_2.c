/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_types_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:09 by acronert          #+#    #+#             */
/*   Updated: 2024/01/12 15:23:21 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int fd, int c)
{
	write (fd, &c, 1);
	return (1);
}

int	ft_print_str(int fd, char *str)
{
	if (!str)
		return (ft_print_str(fd, "(null)"));
	return (write (fd, str, ft_strlen_int(str)));
}

int	ft_print_ptr(int fd, uintptr_t uptr)
{
	if (!uptr)
		return (ft_print_str(fd, "(nil)"));
	else
		return (write (fd, &"0x", 2) + ft_put_ulongint(fd, uptr, LHEX_BASE, 0));
}
