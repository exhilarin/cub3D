/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 11:00:00 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	draw_player_square(t_game *game, t_minimap *mm)
{
	int	screen_x;
	int	screen_y;
	int	i;
	int	j;

	screen_x = mm->player_x - MINIMAP_PLAYER_SIZE / 2;
	screen_y = mm->player_y - MINIMAP_PLAYER_SIZE / 2;
	i = 0;
	while (i < MINIMAP_PLAYER_SIZE)
	{
		j = 0;
		while (j < MINIMAP_PLAYER_SIZE)
		{
			put_pixel_minimap(game, screen_x + j, screen_y + i,
				MINIMAP_PLAYER_COLOR);
			j++;
		}
		i++;
	}
}

void	draw_player_direction(t_game *game, t_minimap *mm)
{
	int		dir_x;
	int		dir_y;
	int		i;
	int		length;

	length = MINIMAP_PLAYER_SIZE;
	dir_x = (int)(game->player.dir_x * length);
	dir_y = (int)(game->player.dir_y * length);
	i = 0;
	while (i < length)
	{
		put_pixel_minimap(game,
			mm->player_x + (dir_x * i) / length,
			mm->player_y + (dir_y * i) / length,
			MINIMAP_DIRECTION_COLOR);
		i++;
	}
}

void	draw_player_on_minimap(t_game *game, t_minimap *mm)
{
	draw_player_square(game, mm);
	draw_player_direction(game, mm);
}