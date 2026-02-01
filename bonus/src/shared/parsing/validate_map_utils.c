/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 01:30:00 by iguney            #+#    #+#             */
/*   Updated: 2026/01/30 02:56:05 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

static char	**create_visited_map(t_game *game)
{
	char	**visited;
	int		y;
	int		x;

	visited = malloc(sizeof(char *) * (game->map.height + 1));
	if (!visited)
		return (NULL);
	y = 0;
	while (y < game->map.height)
	{
		visited[y] = malloc(sizeof(char) * (game->map.width + 1));
		if (!visited[y])
		{
			while (--y >= 0)
				free(visited[y]);
			free(visited);
			return (NULL);
		}
		x = 0;
		while (x < game->map.width)
			visited[y][x++] = '0';
		visited[y][x] = '\0';
		y++;
	}
	visited[y] = NULL;
	return (visited);
}

static void	flood_fill(char **grid, char **visited, int x, int y, int width)
{
	if (y < 0 || x < 0 || !grid[y] || x >= width)
		return ;
	if (x >= (int)ft_strlen(grid[y]) || grid[y][x] == ' '
		|| visited[y][x] == '1')
		return ;
	visited[y][x] = '1';
	flood_fill(grid, visited, x + 1, y, width);
	flood_fill(grid, visited, x - 1, y, width);
	flood_fill(grid, visited, x, y + 1, width);
	flood_fill(grid, visited, x, y - 1, width);
}

static void	find_bounds(char **visited, int *bounds, int y, int x)
{
	if (visited[y][x] == '1')
	{
		if (x < bounds[0])
			bounds[0] = x;
		if (x > bounds[1])
			bounds[1] = x;
		if (y < bounds[2])
			bounds[2] = y;
		if (y > bounds[3])
			bounds[3] = y;
	}
}

static int	get_bounding_box(char **visited, t_game *game, int *bounds)
{
	int	y;
	int	x;

	bounds[0] = 2147483647;
	bounds[1] = -1;
	bounds[2] = 2147483647;
	bounds[3] = -1;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			find_bounds(visited, bounds, y, x);
			x++;
		}
		y++;
	}
	if (bounds[0] == 2147483647)
		return (0);
	return (1);
}

static int	check_outside(t_game *game, char **visited)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			c = game->map.grid[y][x];
			if (c != ' ' && c != '\t' && visited[y][x] != '1')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	validate_map_connectivity(t_game *game)
{
	char	**visited;
	int		bounds[4];
	int		px;
	int		py;

	visited = create_visited_map(game);
	if (!visited)
	{
		free_game(game);
		ft_perror("Error\nMemory allocation failed\n");
	}
	px = (int)game->map.player_x;
	py = (int)game->map.player_y;
	flood_fill(game->map.grid, visited, px, py, game->map.width);
	if (!get_bounding_box(visited, game, bounds))
	{
		free_split(visited);
		free_game(game);
		ft_perror("Error\nMap validation failed\n");
	}
	if (!check_outside(game, visited))
	{
		free_split(visited);
		free_game(game);
		ft_perror("Error\nMap contains disconnected elements\n");
	}
	free_split(visited);
}

