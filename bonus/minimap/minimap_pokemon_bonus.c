/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_pokemon_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 11:00:00 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	get_pokemon_color(int pokemon_type)
{
	if (pokemon_type == POKEMON_PIKACHU)
		return (MINIMAP_PIKACHU_COLOR);
	else if (pokemon_type == POKEMON_SNORLAX)
		return (MINIMAP_SNORLAX_COLOR);
	else if (pokemon_type == POKEMON_CHARIZARD)
		return (MINIMAP_CHARIZARD_COLOR);
	return (0xFFFFFF);
}

static void	draw_pokemon_square(t_game *game, t_minimap *mm, int x, int y, int color)
{
	int	screen_x;
	int	screen_y;
	int	i;
	int	j;

	screen_x = mm->offset_x + (x * mm->tile_size) + (mm->tile_size - MINIMAP_POKEMON_SIZE) / 2;
	screen_y = mm->offset_y + (y * mm->tile_size) + (mm->tile_size - MINIMAP_POKEMON_SIZE) / 2;
	
	i = 0;
	while (i < MINIMAP_POKEMON_SIZE)
	{
		j = 0;
		while (j < MINIMAP_POKEMON_SIZE)
		{
			put_pixel_minimap(game, screen_x + j, screen_y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_door_pokemon(t_game *game, t_minimap *minimap)
{
	t_door	*current_door;
	int		pokemon_color;

	current_door = game->doors;
	while (current_door)
	{
		if (current_door->state == DOOR_CLOSED)
		{
			if (game->map.grid[current_door->map_y][current_door->map_x] == DOOR_PIKACHU)
				pokemon_color = MINIMAP_PIKACHU_COLOR;
			else if (game->map.grid[current_door->map_y][current_door->map_x] == DOOR_SNORLAX)
				pokemon_color = MINIMAP_SNORLAX_COLOR;
			else if (game->map.grid[current_door->map_y][current_door->map_x] == DOOR_CHARIZARD)
				pokemon_color = MINIMAP_CHARIZARD_COLOR;
			else
				pokemon_color = 0xFFFFFF;
			draw_pokemon_square(game, minimap, current_door->map_x, current_door->map_y, pokemon_color);
		}
		current_door = current_door->next;
	}
}

static void	draw_active_pokemon(t_game *game, t_minimap *minimap)
{
	t_pokemon	*current_pokemon;
	int			pokemon_color;

	current_pokemon = game->pokemons;
	while (current_pokemon)
	{
		if (current_pokemon->active)
		{
			pokemon_color = get_pokemon_color(current_pokemon->pokemon_type);
			draw_pokemon_square(game, minimap, current_pokemon->map_x, current_pokemon->map_y, pokemon_color);
		}
		current_pokemon = current_pokemon->next;
	}
}

void	draw_pokemon_on_minimap(t_game *game, t_minimap *minimap)
{
	draw_door_pokemon(game, minimap);
	draw_active_pokemon(game, minimap);
}