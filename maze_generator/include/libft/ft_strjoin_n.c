/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:36:32 by acronert          #+#    #+#             */
/*   Updated: 2024/01/15 10:42:39 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"

// ft_strjoin_n() returns a new string, a concatenation of n strings specified
// 		in parameters. Ensure that the provided number (n) matches the actual
// 		number of strings; otherwise, the behavior is undefined.
char	*ft_strjoin_n(int n, char *first, ...)
{
	va_list	args;
	char	*joined_str;
	char	*tmp;
	int		i;

	if (!first || n <= 0)
		return (NULL);
	joined_str = ft_strdup(first);
	if (!joined_str)
		return (NULL);
	va_start(args, first);
	i = 0;
	while (++i < n)
	{
		tmp = ft_strjoin(joined_str, va_arg(args, char *));
		if (!tmp)
		{
			va_end(args);
			return (NULL);
		}
		free(joined_str);
		joined_str = tmp;
	}
	va_end(args);
	return (joined_str);
}
