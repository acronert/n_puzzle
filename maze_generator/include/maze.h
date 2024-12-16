/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:58:08 by acronert          #+#    #+#             */
/*   Updated: 2024/02/08 16:43:18 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAZE_H
# define MAZE_H

# include "libft.h"
# include <time.h>

# define SUCCESS	0
# define FAILURE	1
# define SPACE		'0'
# define WALL		'1'

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_settings
{
	int	x;
	int	y;
	int	corridor_width;
	int	imperfection;
}		t_settings;

typedef struct s_maze_node
{
	int			link;
	int			south_door;
	int			east_door;
	t_settings	*set;
}		t_maze_node;

char		**ft_create_maze(t_settings *settings);

t_maze_node	**ft_initialize_nodes(t_settings *settings);
t_maze_node	**ft_create_doors(t_maze_node **node);

void		ft_free_node(t_maze_node **node);

t_maze_node	**ft_create_doors(t_maze_node **node);

#endif