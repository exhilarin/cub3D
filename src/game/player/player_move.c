/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 23:08:20 by iguney            #+#    #+#             */
/*   Updated: 2026/01/24 16:35:25 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void rotate_player(t_game *game)
{
    double old_dir_x;
    double old_plane_x;
    double rotation_speed;

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

static int collision_detection(t_game *game)
{
	int map_x;
	int map_y;
	double margin;

	margin = 0.05;

	map_x = (int)(game->player.new_x - margin);
	map_y = (int)(game->player.new_y - margin);
	if (map_x < 0 || map_y < 0 || map_y >= game->map.height || map_x >= game->map.width)
		return 0;
	if (game->map.grid[map_y][map_x] == '1')
		return 0;
		
	map_x = (int)(game->player.new_x + margin);
	map_y = (int)(game->player.new_y - margin);
	if (map_x < 0 || map_y < 0 || map_y >= game->map.height || map_x >= game->map.width)
		return 0;
	if (game->map.grid[map_y][map_x] == '1')
		return 0;
		
	map_x = (int)(game->player.new_x - margin);
	map_y = (int)(game->player.new_y + margin);
	if (map_x < 0 || map_y < 0 || map_y >= game->map.height || map_x >= game->map.width)
		return 0;
	if (game->map.grid[map_y][map_x] == '1')
		return 0;
		
	map_x = (int)(game->player.new_x + margin);
	map_y = (int)(game->player.new_y + margin);
	if (map_x < 0 || map_y < 0 || map_y >= game->map.height || map_x >= game->map.width)
		return 0;
	if (game->map.grid[map_y][map_x] == '1')
		return 0;
		
	return 1;
}

static void move(t_game *game)
{
	game->player.x = game->player.new_x;
	game->player.y = game->player.new_y;
}

static void	move_player(t_game *game)
{
	game->player.new_x = game->player.x;
	game->player.new_y = game->player.y;
	if (game->player.move_forward)
	{
		game->player.new_x += game->player.dir_x * game->player.move_speed;
		game->player.new_y += game->player.dir_y * game->player.move_speed;
	}
	if (game->player.move_backward)
	{
		game->player.new_x -= game->player.dir_x * game->player.move_speed;
		game->player.new_y -= game->player.dir_y * game->player.move_speed;
	}
	if (game->player.move_right)
	{
		game->player.new_x += game->player.plane_x * game->player.move_speed;
		game->player.new_y += game->player.plane_y * game->player.move_speed;
	}
	if (game->player.move_left)
	{
		game->player.new_x -= game->player.plane_x * game->player.move_speed;
		game->player.new_y -= game->player.plane_y * game->player.move_speed;
	}
	if (collision_detection(game))
        move(game);
}

void update_player(t_game *game)
{
    move_player(game);
    rotate_player(game);
}