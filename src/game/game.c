/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/01/30 01:10:12 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_window(t_game *game)
{
	mlx_loop_end(game->mlx);
	free_game(game);
	exit(0);
	return (0);
}

void	game_loop(t_game *game)
{
	init_mlx(game);
	init_player(game);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, LENGHT / 2, HEIGHT / 2);
	key_hook(game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, (void *)render_frame, game);
	mlx_loop(game->mlx);
}

void	exit_game(t_game *game)
{
	mlx_loop_end(game->mlx);
	free_game(game);
	exit(0);
}
