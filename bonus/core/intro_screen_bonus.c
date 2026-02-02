/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro_screen_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/02 22:25:59 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_intro_screen_bonus(t_game *game)
{
	game->intro_screen.img = mlx_xpm_file_to_image(game->mlx,
			"assets/Pokemon3D_Intro.xpm",
			&game->intro_screen.width,
			&game->intro_screen.height);
	if (!game->intro_screen.img)
	{
		ft_perror("Error\nFailed to load intro screen\n");
	}
	game->intro_screen.addr = mlx_get_data_addr(game->intro_screen.img,
			&game->intro_screen.bpp,
			&game->intro_screen.line_lenght,
			&game->intro_screen.endian);
}

void	show_intro_screen_bonus(t_game *game)
{
	int		x_offset;
	int		y_offset;

	if (game->intro_screen.width == LENGHT
		&& game->intro_screen.height == HEIGHT)
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->intro_screen.img, 0, 0);
		return ;
	}
	x_offset = (LENGHT - game->intro_screen.width) / 2;
	y_offset = (HEIGHT - game->intro_screen.height) / 2;
	if (x_offset < 0)
		x_offset = 0;
	if (y_offset < 0)
		y_offset = 0;
	mlx_put_image_to_window(game->mlx, game->win,
		game->intro_screen.img, x_offset, y_offset);
}

void	start_game_bonus(t_game *game)
{
	game->intro_active = 0;
	if (game->intro_screen.img)
	{
		mlx_destroy_image(game->mlx, game->intro_screen.img);
		game->intro_screen.img = NULL;
	}
	init_player(game);
}
