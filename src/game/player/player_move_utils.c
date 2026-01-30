/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/01/30 02:58:38 by iguney           ###   ########.fr       */
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

int	handle_mouse_move(int x, int y, t_game *game)
{
	int		delta_x;
	double	rotation;
	double	old_dir_x;
	double	old_plane_x;

	(void)y;
	delta_x = x - game->player.last_mouse_x;
	if (delta_x != 0)
	{
		rotation = delta_x * 0.0015;
		old_dir_x = game->player.dir_x;
		old_plane_x = game->player.plane_x;
		game->player.dir_x = game->player.dir_x * cos(rotation)
			- game->player.dir_y * sin(rotation);
		game->player.dir_y = old_dir_x * sin(rotation)
			+ game->player.dir_y * cos(rotation);
		game->player.plane_x = game->player.plane_x * cos(rotation)
			- game->player.plane_y * sin(rotation);
		game->player.plane_y = old_plane_x * sin(rotation)
			+ game->player.plane_y * cos(rotation);
		mlx_mouse_move(game->mlx, game->win, LENGHT / 2, HEIGHT / 2);
	}
	game->player.last_mouse_x = LENGHT / 2;
	return (0);
}
