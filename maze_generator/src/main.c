/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:56:00 by acronert          #+#    #+#             */
/*   Updated: 2024/02/13 13:55:26 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"

void	ft_display_maze(char **maze)
{
	int	x;
	int	y;

	x = 0;
	while (maze[0][x++]) {
		;
	}

	y = 0;
	while (maze[y++]) {
		;
	}
	printf("%d\n%d\n", x - 1, y - 1);

	y = 0;
	while (maze[y])
	{
		x = 0;
		while (maze[y][x])
		{
			// if (maze[y][x] == '1')
			// 	printf("██");
			// else
			// 	printf("  ");
			printf("%c", maze[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

int	ft_checkatoi(char *str, int n)
{
	char	*strn;

	strn = ft_itoa(n);
	if (!strn)
		return (FAILURE);
	if (ft_strncmp(str, strn, ft_strlen(str)))
	{
		free(strn);
		return (FAILURE);
	}
	free(strn);
	return (SUCCESS);
}

t_settings	*ft_parse(int argc, char **argv)
{
	t_settings	*settings;

	if (argc < 3 || argc > 5)
		return (NULL);
	settings = malloc(sizeof(t_settings));
	settings->x = ft_atoi(argv[1]);
	if (settings->x <= 0 || ft_checkatoi(argv[1], settings->x))
		return (free(settings), NULL);
	settings->y = ft_atoi(argv[2]);
	if (settings->y <= 0 || ft_checkatoi(argv[2], settings->y))
		return (free(settings), NULL);
	if (argc >= 4)
	{
		settings->corridor_width = ft_atoi(argv[3]);
		if (settings->corridor_width <= 0
			|| ft_checkatoi(argv[3], settings->corridor_width))
			return (free(settings), NULL);
	}
	else
		settings->corridor_width = 1;
	if (argc == 5)
	{
		settings->imperfection = ft_atoi(argv[4]);
		if (settings->imperfection < 0 || settings->imperfection > 100
			|| ft_checkatoi(argv[4], settings->imperfection))
			return (free(settings), NULL);
		settings->imperfection = (settings->y * settings->x * settings->imperfection) / 100; //percentage
	}
	else
		settings->imperfection = 0;
	return (settings);
}

int	main(int argc, char **argv)
{
	char		**maze;
	t_settings	*settings;

	settings = ft_parse(argc, argv);
	if (!settings)
	{
		printf("Incorrect arguments\n./maze_generator NODE_WIDTH NODE_HEIGHT [CORRIDOR_WIDTH] [IMPERFECTION_PERCENT]\n");
		return (1);
	}
	maze = ft_create_maze(settings);
	ft_display_maze(maze);
	ft_free_double_char(maze);
	return (0);
}
