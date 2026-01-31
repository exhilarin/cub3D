/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 00:54:35 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_mouse_bonus(t_game *game)
{
	mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, LENGHT / 2, HEIGHT / 2);
	game->player.last_mouse_x = LENGHT / 2;
}

int	handle_mouse_move_bonus(int x, int y, t_game *game)
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
