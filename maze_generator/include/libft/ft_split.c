/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:18:37 by acronert          #+#    #+#             */
/*   Updated: 2024/01/12 16:46:41 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char *str, char sep)
{
	int	words;
	int	i;

	if (!*str)
		return (0);
	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] != sep && (str[i + 1] == sep || !str[i + 1]))
			words++;
		i++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		index;
	int		start;

	tab = malloc((ft_countwords((char *)s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	index = 0;
	start = -1;
	while ((size_t)i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || !s[i]) && start >= 0)
		{
			tab[index] = ft_substr(s, start, i - start);
			start = -1;
			index++;
		}
		i++;
	}
	tab[index] = 0;
	return (tab);
}
