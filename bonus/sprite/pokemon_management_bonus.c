/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pokemon_management_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 11:30:00 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	init_pokemon_bonus(t_game *game)
{
	t_door		*door;
	t_pokemon	*new_poke;
	t_pokemon	*current;
	int			poke_type;

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
		new_poke->fading = 0;
		new_poke->alpha = MAX_ALPHA;
		new_poke->sprite = NULL;
		new_poke->current_frame = 0;
		poke_type = get_pokemon_type(game->map.grid[door->map_y][door->map_x]);
		new_poke->pokemon_type = poke_type;
		if (poke_type == POKEMON_PIKACHU)
			load_pikachu_frames(game, new_poke);
		else if (poke_type == POKEMON_SNORLAX)
			load_snorlax_frames(game, new_poke);
		else if (poke_type == POKEMON_CHARIZARD)
			load_charizard_frames(game, new_poke);
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

void	update_pokemon_bonus(t_game *game)
{
	t_pokemon	*current;

	current = game->pokemons;
	while (current)
	{
		if (current->fading == 1)
		{
			current->alpha -= FADE_SPEED;
			if (current->alpha <= 0)
			{
				current->active = 0;
				current->alpha = 0;
				current->fading = 0;
			}
		}
		else if (current->fading == 2)
		{
			if (current->alpha == 0)
				current->alpha = FADE_SPEED;
			else
				current->alpha += FADE_SPEED;
			if (current->alpha >= MAX_ALPHA)
			{
				current->active = 1;
				current->alpha = MAX_ALPHA;
				current->fading = 0;
			}
		}
		if (current->active && current->fading == 0)
		{
			current->anim_offset++;
				if (current->anim_offset > 100)
					current->anim_offset = 0;
			if (current->pokemon_type == POKEMON_PIKACHU)
			{
				if (current->anim_offset % 10 == 0)
					current->current_frame = (current->current_frame + 1)
						% PIKACHU_FRAMES;
			}
			else if (current->pokemon_type == POKEMON_SNORLAX)
			{
				if (current->anim_offset % 5 == 0)
					current->current_frame = (current->current_frame + 1)
						% SNORLAX_FRAMES;
			}
			else if (current->pokemon_type == POKEMON_CHARIZARD)
			{
				if (current->anim_offset % 10 == 0)
					current->current_frame = (current->current_frame + 1)
						% CHARIZARD_FRAMES;
			}
		}
		current = current->next;
	}
}

static void	free_pokemon_frames(t_game *game, t_pokemon *current)
{
	int	i;

	if (current->pokemon_type == POKEMON_PIKACHU)
	{
		i = 0;
		while (i < PIKACHU_FRAMES)
		{
			if (current->pikachu_frames[i].img)
				mlx_destroy_image(game->mlx, current->pikachu_frames[i].img);
			i++;
		}
	}
	else if (current->pokemon_type == POKEMON_SNORLAX)
	{
		i = 0;
		while (i < SNORLAX_FRAMES)
		{
			if (current->snorlax_frames[i].img)
				mlx_destroy_image(game->mlx, current->snorlax_frames[i].img);
			i++;
		}
	}
	else if (current->pokemon_type == POKEMON_CHARIZARD)
	{
		i = 0;
		while (i < CHARIZARD_FRAMES)
		{
			if (current->charizard_frames[i].img)
				mlx_destroy_image(game->mlx, current->charizard_frames[i].img);
			i++;
		}
	}
}

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
		free_pokemon_frames(game, current);
		free(current);
		current = next;
	}
	game->pokemons = NULL;
}