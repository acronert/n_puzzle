/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_maze.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:25:24 by acronert          #+#    #+#             */
/*   Updated: 2024/02/08 17:14:01 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"

char	**ft_initialize_map(t_coord *map_size)
{
	char	**map;
	int		i;

	map = malloc((map_size->y + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	map[map_size->y] = NULL;
	i = 0;
	while (i < map_size->y)
	{
		map[i] = malloc((map_size->x + 1) * sizeof(char));
		if (!map[i])
			return (NULL);
		map[i][map_size->x] = '\0';
		i++;
	}
	return (map);
}

char	ft_calculate_wall(t_maze_node **node, t_coord map_size, int x, int y)
{
	int	width;

	width = 1 + node[0][0].set->corridor_width;
	if (y == 0 || y == map_size.y - 1 || x == 0 || x == map_size.x - 1)
		return (WALL);
	else if (y % width != 0 && x % width != 0)
		return (SPACE);
	else if (y % width == 0 && x % width == 0)
		return (WALL);
	else if (y % width != 0 && x % width == 0)
		return (!(node[(y - 1) / width][(x / width) - 1].east_door) + '0');
	else if (y % width == 0 && x % width != 0)
		return (!(node[(y / width) - 1][(x - 1) / width].south_door) + '0');
	return (0);
}

t_maze_node **ft_imperfect_maze(t_maze_node **node)
{
	int	rand_y;
	int	rand_x;
	int	rand_door;

	while (1)
	{
		rand_y = rand() % node[0][0].set->y;
		rand_x = rand() % node[0][0].set->x;
		rand_door = rand() % 2;
		if (!node[rand_y][rand_x].south_door && rand_door == 0)
		{
			node[rand_y][rand_x].south_door = 1;
			break;
		}
		else if (!node[rand_y][rand_x].east_door && rand_door == 1)
		{
			node[rand_y][rand_x].east_door = 1;
			break ;
		}
	}
	return (node);
}

char	**ft_clean_map(char **map, t_coord map_size)
{
	int	x;
	int	y;

	y = 1;
	while (y < map_size.y - 1)
	{
		x = 1;
		while (x < map_size.x -1)
		{
			if (map[y][x] == WALL && map[y + 1][x] == SPACE
				&& map[y - 1][x] == SPACE && map[y][x + 1] == SPACE
				&& map[y][x - 1] == SPACE)
				map[y][x] = SPACE;
			x++;
		}
		y++;
		
	}
	return (map);
}

char	**ft_nodes_to_maze(t_maze_node **node)
{
	char	**map;
	t_coord	map_size;
	int		x;
	int		y;
	int		width;

	width = 1 + node[0][0].set->corridor_width;
	map_size.x = node[0][0].set->x * width + 1;
	map_size.y = node[0][0].set->y * width + 1;
	while (node[0][0].set->imperfection--)
		node = ft_imperfect_maze(node);
	map = ft_initialize_map(&map_size);
	if (!map)
		return (NULL);
	x = -1;
	while (++x < map_size.x)
	{
		y = -1;
		while (++y < map_size.y)
			map[y][x] = ft_calculate_wall(node, map_size, x, y);
	}
	map = ft_clean_map(map, map_size);
	return (map);
}

char	**ft_create_maze(t_settings *settings)
{
	t_maze_node	**node;
	char		**maze;

	node = ft_initialize_nodes(settings);
	if (!node)
		return (NULL);
	maze = ft_nodes_to_maze(node);
	ft_free_node(node);
	return (maze);
}
