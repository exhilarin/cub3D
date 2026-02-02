/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_interaction_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/02 17:04:40 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include <sys/time.h>

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
	char		cell;
	int			player_x;
	int			player_y;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	player_x = (int)game->player.x;
	player_y = (int)game->player.y;
	current = game->pokemons;
	while (current)
	{
		if (current->map_x == x && current->map_y == y)
		{
			if (current->active)
			{
				current->fading = 1;
				current->fade_start_time = tv.tv_sec + tv.tv_usec / 1000000.0;
				game->map.grid[y][x] = '0';
			}
			else if (player_x != x || player_y != y)
			{
				current->fading = 2;
				current->fade_start_time = tv.tv_sec + tv.tv_usec / 1000000.0;
				if (current->pokemon_type == POKEMON_PIKACHU)
					cell = 'P';
				else if (current->pokemon_type == POKEMON_SNORLAX)
					cell = 'B';
				else if (current->pokemon_type == POKEMON_CHARIZARD)
					cell = 'C';
				else
					cell = '0';
				game->map.grid[y][x] = cell;
			}
			return ;
		}
		current = current->next;
	}
}

static void	check_door_distance(t_game *game, t_door *door, 
							t_door_search *search)
{
	if (!is_player_near_door(game, door))
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
	if (door->state == DOOR_CLOSED)
	{
		door->state = DOOR_OPENING;
		game->anim.type = ANIM_POKEBALL;
		game->anim.frame_count = 0;
		game->anim.map_x = door->map_x;
		game->anim.map_y = door->map_y;
	}
	else if (door->state == DOOR_OPEN)
		door->state = DOOR_CLOSED;
	deactivate_pokemon_at(game, door->map_x, door->map_y);
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
