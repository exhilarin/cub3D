/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 23:08:20 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 07:05:54 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_player(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotation_speed;

	rotation_speed = 0;
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	if (game->player.rotate_left)
		rotation_speed -= game->player.rotate_speed;
	if (game->player.rotate_right)
		rotation_speed += game->player.rotate_speed;
	if (rotation_speed != 0)
	{
		game->player.dir_x = game->player.dir_x * cos(rotation_speed)
			- game->player.dir_y * sin(rotation_speed);
		game->player.dir_y = old_dir_x * sin(rotation_speed)
			+ game->player.dir_y * cos(rotation_speed);
		game->player.plane_x = game->player.plane_x * cos(rotation_speed)
			- game->player.plane_y * sin(rotation_speed);
		game->player.plane_y = old_plane_x * sin(rotation_speed)
			+ game->player.plane_y * cos(rotation_speed);
	}
}

static void	move_player(t_game *game)
{
	if (game->player.move_forward)
	{
		game->player.x += game->player.dir_x * game->player.current_speed;
		game->player.y += game->player.dir_y * game->player.current_speed;
	}
	if (game->player.move_backward)
	{
		game->player.x -= game->player.dir_x * game->player.current_speed;
		game->player.y -= game->player.dir_y * game->player.current_speed;
	}
	if (game->player.move_right)
	{
		game->player.x += game->player.plane_x * game->player.current_speed;
		game->player.y += game->player.plane_y * game->player.current_speed;
	}
	if (game->player.move_left)
	{
		game->player.x -= game->player.plane_x * game->player.current_speed;
		game->player.y -= game->player.plane_y * game->player.current_speed;
	}
}

void	update_player(t_game *game)
{
	move_player(game);
	rotate_player(game);
}

void	update_player_speed(t_game *game)
{
	int	moving;

	moving = game->player.move_forward || game->player.move_backward
		|| game->player.move_left || game->player.move_right;
	if (moving)
		game->player.current_speed = game->player.move_speed;
	else
		game->player.current_speed = 0;
}
