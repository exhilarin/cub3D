/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_interaction_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 22:52:19 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

typedef struct s_door_search
{
	t_door	*closest;
	double	min_dist;
	double	dx;
	double	dy;
	double	dist;
}	t_door_search;

static void	deactivate_pokemon_at(t_game *game, int x, int y)
{
	t_pokemon	*current;

	current = game->pokemons;
	while (current)
	{
		if (current->map_x == x && current->map_y == y && current->active)
		{
			current->fading = 1;
			return ;
		}
		current = current->next;
	}
}

static void	check_door_distance(t_game *game, t_door *door, 
							t_door_search *search)
{
	if (door->state != DOOR_CLOSED || !is_player_near_door(game, door))
		return ;
	search->dx = game->player.x - (door->map_x + 0.5);
	search->dy = game->player.y - (door->map_y + 0.5);
	search->dist = sqrt(search->dx * search->dx + search->dy * search->dy);
	if (search->dist < search->min_dist)
	{
		search->min_dist = search->dist;
		search->closest = door;
	}
}

static void	open_door(t_game *game, t_door *door)
{
	door->state = DOOR_OPENING;
	game->anim.type = ANIM_POKEBALL;
	game->anim.frame_count = 0;
	game->anim.map_x = door->map_x;
	game->anim.map_y = door->map_y;
	deactivate_pokemon_at(game, door->map_x, door->map_y);
	remove_door_from_map(game, door->map_x, door->map_y);
}

void	trigger_door_bonus(t_game *game)
{
	t_door			*door;
	t_door_search	search;

	search.closest = NULL;
	search.min_dist = DOOR_INTERACT_DIST;
	door = game->doors;
	while (door)
	{
		check_door_distance(game, door, &search);
		door = door->next;
	}
	if (search.closest)
		open_door(game, search.closest);
}

void	update_doors_bonus(t_game *game)
{
	t_door	*current;

	current = game->doors;
	while (current)
	{
		if (current->state == DOOR_OPENING)
			current->state = DOOR_OPEN;
		current = current->next;
	}
}

void	draw_doors_bonus(t_game *game)
{
	(void)game;
}
