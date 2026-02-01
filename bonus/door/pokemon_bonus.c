/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pokemon_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 02:25:15 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/* Initialize Pokemon sprites for each door */
void	init_pokemon_bonus(t_game *game)
{
	t_door		*door;
	t_pokemon	*new_poke;
	t_pokemon	*current;

	game->pokemons = NULL;
	door = game->doors;
	while (door)
	{
		new_poke = (t_pokemon *)malloc(sizeof(t_pokemon));
		if (!new_poke)
			return ;
		new_poke->map_x = door->map_x;
		new_poke->map_y = door->map_y;
		new_poke->anim_offset = 0;
		new_poke->active = 1;
		new_poke->sprite = NULL;
		new_poke->next = NULL;
		if (!game->pokemons)
			game->pokemons = new_poke;
		else
		{
			current = game->pokemons;
			while (current->next)
				current = current->next;
			current->next = new_poke;
		}
		door = door->next;
	}
}

/* Update Pokemon animation (simple bobbing effect) */
void	update_pokemon_bonus(t_game *game)
{
	t_pokemon	*current;

	current = game->pokemons;
	while (current)
	{
		if (current->active)
		{
			current->anim_offset++;
			if (current->anim_offset > 100)
				current->anim_offset = 0;
		}
		current = current->next;
	}
}

/* Draw Pokemon sprites (placeholder - actual rendering in raycasting) */
void	draw_pokemon_bonus(t_game *game)
{
	(void)game;
}

/* Free all Pokemon sprites */
void	free_pokemon_bonus(t_game *game)
{
	t_pokemon	*current;
	t_pokemon	*next;

	current = game->pokemons;
	while (current)
	{
		next = current->next;
		if (current->sprite)
			mlx_destroy_image(game->mlx, current->sprite);
		free(current);
		current = next;
	}
	game->pokemons = NULL;
}
