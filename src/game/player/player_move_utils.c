/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/01/27 01:55:53 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || y >= game->map.height || x >= game->map.width)
		return (0);
	if (game->map.grid[y][x] == '1')
		return (0);
	return (1);
}

void	move(t_game *game)
{
	game->player.x = game->player.new_x;
	game->player.y = game->player.new_y;
}
