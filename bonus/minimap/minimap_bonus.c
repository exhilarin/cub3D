/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 10:56:58 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	update_player_position(t_game *game, t_minimap *minimap)
{
	minimap->player_x = minimap->offset_x
		+ (int)(game->player.x * minimap->tile_size);
	minimap->player_y = minimap->offset_y
		+ (int)(game->player.y * minimap->tile_size);
}

void	init_minimap(t_game *game, t_minimap *minimap)
{
	int	max_dimension;

	if (!minimap)
		return ;
	minimap->size = MINIMAP_SIZE;
	minimap->offset_x = MINIMAP_MARGIN;
	minimap->offset_y = MINIMAP_MARGIN;
	if (game->map.width > game->map.height)
		max_dimension = game->map.width;
	else
		max_dimension = game->map.height;
	if (max_dimension == 0)
		max_dimension = 1;
	minimap->tile_size = minimap->size / max_dimension;
	if (minimap->tile_size < 1)
		minimap->tile_size = 1;
	update_player_position(game, minimap);
}

void	draw_minimap(t_game *game, t_minimap *minimap)
{
	int	mx;
	int	my;

	if (!minimap)
		return ;
	update_player_position(game, minimap);
	my = 0;
	while (my < game->map.height)
	{
		mx = 0;
		while (mx < game->map.width)
		{
			draw_minimap_tile(game, minimap, mx, my);
			mx++;
		}
		my++;
	}
	draw_player_on_minimap(game, minimap);
	draw_pokemon_on_minimap(game, minimap);
}

void	draw_minimap_with_border(t_game *game, t_minimap *minimap)
{
	int	mx;
	int	my;

	if (!minimap)
		return ;
	update_player_position(game, minimap);
	my = 0;
	while (my < game->map.height)
	{
		mx = 0;
		while (mx < game->map.width)
		{
			draw_minimap_tile(game, minimap, mx, my);
			mx++;
		}
		my++;
	}
	draw_player_on_minimap(game, minimap);
	draw_pokemon_on_minimap(game, minimap);
}
