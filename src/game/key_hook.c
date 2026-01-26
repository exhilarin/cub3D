/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/01/27 01:32:35 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.move_forward = 1;
	else if (keycode == KEY_S)
		game->player.move_backward = 1;
	else if (keycode == KEY_A)
		game->player.move_left = 1;
	else if (keycode == KEY_D)
		game->player.move_right = 1;
	else if (keycode == KEY_LEFT)
		game->player.rotate_left = 1;
	else if (keycode == KEY_RIGHT)
		game->player.rotate_right = 1;
	else if (keycode == KEY_ESC)
		exit_game(game);
	return (0);
}

static int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.move_forward = 0;
	else if (keycode == KEY_S)
		game->player.move_backward = 0;
	else if (keycode == KEY_A)
		game->player.move_left = 0;
	else if (keycode == KEY_D)
		game->player.move_right = 0;
	else if (keycode == KEY_LEFT)
		game->player.rotate_left = 0;
	else if (keycode == KEY_RIGHT)
		game->player.rotate_right = 0;
	return (0);
}

void	key_hook(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
}
