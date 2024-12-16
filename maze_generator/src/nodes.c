/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:33:03 by acronert          #+#    #+#             */
/*   Updated: 2024/02/08 16:26:37 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"

void	ft_free_node(t_maze_node **node)
{
	int	y;
	int	len;

	y = 0;
	len = node[0][0].set->y;
	free(node[0][0].set);
	while (y < len)
	{
		free(node[y]);
		y++;
	}
	free(node);
}

t_maze_node	**ft_set_default_node(t_maze_node **node, t_settings *settings)
{
	int	y;
	int	x;

	y = -1;
	while (++y < settings->y)
	{
		x = -1;
		node[y] = malloc(settings->x * sizeof(t_maze_node));
		if (!node[y])
			return (NULL);
		while (++x < settings->x)
		{
			node[y][x].south_door = 0;
			node[y][x].east_door = 0;
			node[y][x].link = y * settings->x + x;
			node[y][x].set = settings;
		}
	}
	return (node);
}

t_maze_node	**ft_initialize_nodes(t_settings *settings)
{
	t_maze_node	**node;

	node = malloc(settings->y * sizeof(t_maze_node *));
	if (!node)
		return (NULL);
	node = ft_set_default_node(node, settings);
	return (node);
}
