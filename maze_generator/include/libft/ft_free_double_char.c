/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:31:41 by acronert          #+#    #+#             */
/*   Updated: 2024/01/18 15:28:58 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double_char(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_free_triple_char(char ***arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr && arr[i])
	{
		ft_free_double_char(arr[i]);
		i++;
	}
	free(arr);
}
