/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 02:25:14 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	game->player.new_x = game->player.x;
	game->player.new_y = game->player.y;
	if (game->player.move_forward)
	{
		game->player.new_x += game->player.dir_x * game->player.current_speed;
		game->player.new_y += game->player.dir_y * game->player.current_speed;
	}
	if (game->player.move_backward)
	{
		game->player.new_x -= game->player.dir_x * game->player.current_speed;
		game->player.new_y -= game->player.dir_y * game->player.current_speed;
	}
	if (game->player.move_right)
	{
		game->player.new_x += game->player.plane_x * game->player.current_speed;
		game->player.new_y += game->player.plane_y * game->player.current_speed;
	}
	if (game->player.move_left)
	{
		game->player.new_x -= game->player.plane_x * game->player.current_speed;
		game->player.new_y -= game->player.plane_y * game->player.current_speed;
	}
	if (collision_detection_bonus(game))
		move_bonus(game);
}

void	update_player_bonus(t_game *game)
{
	move_player(game);
	rotate_player(game);
}

void	update_player_speed_bonus(t_game *game)
{
	int	moving;

	moving = game->player.move_forward || game->player.move_backward
		|| game->player.move_left || game->player.move_right;
	if (moving)
		game->player.current_speed = game->player.move_speed;
	else
		game->player.current_speed = 0;
	if (game->player.shift_pressed && moving)
		game->player.current_speed *= SLOW_WALK_FACTOR;
}
