/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agedikog <agedikog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:53:49 by agedikog          #+#    #+#             */
/*   Updated: 2025/12/21 17:07:56 by agedikog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	check_player(t_game *game, int x, int y)
{
	char	c;

	c = game->map.grid[y][x];
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
    {
        if (game->map.player_count > 0)
            ft_perror("Error\nMultiple player start positions found\n");
        game->map.player_count++;
        game->map.player_dir = c;
        game->map.player_x = x + 0.5;
        game->map.player_y = y + 0.5;
    }
}

static int	is_surrounded(t_game *game, int x, int y)
{
	char	**grid;
	int		height;
	int		row_len;

	grid = game->map.grid;
    height = game->map.height;
    if (y == 0 || y == height - 1 || x == 0 || x == (int)ft_strlen(grid[y]) - 1)
        return (0);
    row_len = ft_strlen(grid[y - 1]);
    if (x >= row_len || grid[y - 1][x] == ' ' || grid[y - 1][x] == '\t')
        return (0);
    row_len = ft_strlen(grid[y + 1]);
    if (x >= row_len || grid[y + 1][x] == ' ' || grid[y + 1][x] == '\t')
        return (0);
    if (grid[y][x - 1] == ' ' || grid[y][x + 1] == ' '
        || grid[y][x - 1] == '\t' || grid[y][x + 1] == '\t')
        return (0);
    return (1);
}

static void	validate_cell(t_game *game, int x, int y)
{
	if (!is_valid_map_char(game->map.grid[y][x]))
		ft_perror("Error\nInvalid character in map\n");
	check_player(game, x, y);
	if (game->map.grid[y][x] == '0'
		|| ft_strchr("NSEW", game->map.grid[y][x]))
	{
		if (!is_surrounded(game, x, y))
			ft_perror("Error\nMap is not enclosed by walls\n");
	}
}

void	validate_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	game->map.player_count = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			validate_cell(game, x, y);
			x++;
		}
		y++;
	}
	if (game->map.player_count != 1)
		ft_perror("Error\nMap must have exactly one player start position\n");
}
