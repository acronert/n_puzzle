/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:40:33 by acronert          #+#    #+#             */
/*   Updated: 2024/01/12 15:25:28 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include "libft.h"

# define DEC_BASE	"0123456789"
# define UHEX_BASE	"0123456789ABCDEF"
# define LHEX_BASE	"0123456789abcdef"

int		ft_printf(int fd, const char *format, ...);
int		ft_check_type(int fd, char *str, va_list args);
int		read_format(int fd, char *str, va_list args);

int		ft_print_char(int fd, int n);
int		ft_print_str(int fd, char *str);
int		ft_print_ptr(int fd, uintptr_t uptr);

int		ft_print_dec(int fd, int n);
int		ft_print_int(int fd, int n);
int		ft_print_udec(int fd, unsigned int n);
int		ft_print_lowhex(int fd, unsigned int n);
int		ft_print_upphex(int fd, unsigned int n);

int		ft_put_ulongint(int fd, unsigned long int n, char *base, int len);
int		ft_put_longint(int fd, long int n, int len);
int		ft_strlen_int(char *str);

#endif
