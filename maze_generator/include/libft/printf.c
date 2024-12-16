/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:02:42 by acronert          #+#    #+#             */
/*   Updated: 2024/01/12 15:20:19 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_type(int fd, char *str, va_list args)
{
	size_t	len;

	len = 1;
	if (*str == 'c')
		len = ft_print_char(fd, va_arg(args, int));
	else if (*str == 's')
		len = ft_print_str(fd, va_arg(args, char *));
	else if (*str == 'p')
		len = ft_print_ptr(fd, va_arg(args, uintptr_t));
	else if (*str == 'd')
		len = ft_print_dec(fd, va_arg(args, int));
	else if (*str == 'i')
		len = ft_print_int(fd, va_arg(args, int));
	else if (*str == 'u')
		len = ft_print_udec(fd, va_arg(args, unsigned int));
	else if (*str == 'x')
		len = ft_print_lowhex(fd, va_arg(args, int));
	else if (*str == 'X')
		len = ft_print_upphex(fd, va_arg(args, int));
	else if (*str == '%')
		write (1, &"%%", 1);
	return (len);
}

int	ft_printf(int fd, const char *format, ...)
{
	va_list	args;
	int		return_value;
	char	*str;

	if (!format)
		return (-1);
	va_start(args, format);
	str = ft_strdup(format);
	if (!str)
		return (-1);
	return_value = read_format(fd, str, args);
	va_end(args);
	free(str);
	return (return_value);
}

int	read_format(int fd, char *str, va_list args)
{
	int		return_value;
	int		i;

	return_value = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != '%')
		{
			ft_print_char(fd, str[i]);
			return_value++;
		}
		else
		{
			i++;
			return_value += ft_check_type(fd, &str[i], args);
		}
	}
	return (return_value);
}
