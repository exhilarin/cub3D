/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 10:29:03 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	check_solid_pokemon(t_game *game, int x, int y)
{
	char	cell;

	if (x < 0 || y < 0 || y >= game->map.height || x >= game->map.width)
		return (0);
	cell = game->map.grid[y][x];
	if (cell == DOOR_SNORLAX || cell == DOOR_CHARIZARD)
		return (1);
	return (0);
}

int	check_wall_bonus(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || y >= game->map.height || x >= game->map.width)
		return (0);
	if (game->map.grid[y][x] == '1')
		return (0);
	/* Also check for solid Pokemon that should act like walls */
	if (check_solid_pokemon(game, x, y))
		return (0);
	return (1);
}

void	move_bonus(t_game *game)
{
	game->player.x = game->player.new_x;
	game->player.y = game->player.new_y;
}

int	collision_detection_bonus(t_game *game)
{
	int		map_x;
	int		map_y;
	double	margin;

	margin = 0.05;
	map_x = (int)(game->player.new_x - margin);
	map_y = (int)(game->player.new_y - margin);
	if (!check_wall_bonus(game, map_x, map_y))
		return (0);
	map_x = (int)(game->player.new_x + margin);
	if (!check_wall_bonus(game, map_x, map_y))
		return (0);
	map_y = (int)(game->player.new_y + margin);
	if (!check_wall_bonus(game, map_x, map_y))
		return (0);
	map_x = (int)(game->player.new_x - margin);
	if (!check_wall_bonus(game, map_x, map_y))
		return (0);
	return (1);
}
