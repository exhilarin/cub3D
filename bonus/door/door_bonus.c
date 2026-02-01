/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 09:54:38 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

/* Helper: Check if character is a door */
int	is_door_char(char c)
{
	return (c == DOOR_PIKACHU || c == DOOR_SNORLAX || c == DOOR_CHARIZARD);
}

/* Helper: Get pokemon type from door character */
int	get_pokemon_type(char c)
{
	if (c == DOOR_PIKACHU)
		return (POKEMON_PIKACHU);
	else if (c == DOOR_SNORLAX)
		return (POKEMON_SNORLAX);
	else if (c == DOOR_CHARIZARD)
		return (POKEMON_CHARIZARD);
	return (POKEMON_PIKACHU);
}

/* Helper: Check if player is near a door (within interaction distance) */
int	is_player_near_door(t_game *game, t_door *door)
{
	double	dx;
	double	dy;
	double	distance;

	dx = game->player.x - (door->map_x + 0.5);
	dy = game->player.y - (door->map_y + 0.5);
	distance = sqrt(dx * dx + dy * dy);
	return (distance < DOOR_INTERACT_DIST);
}

/* Helper: Find door at specific coordinates */
t_door	*find_door_at(t_game *game, int x, int y)
{
	t_door	*current;

	current = game->doors;
	while (current)
	{
		if (current->map_x == x && current->map_y == y)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/* Helper: Add a new door to the linked list */
void	add_door_to_list(t_game *game, int x, int y)
{
	t_door	*new_door;
	t_door	*current;

	new_door = (t_door *)malloc(sizeof(t_door));
	if (!new_door)
		return ;
	new_door->map_x = x;
	new_door->map_y = y;
	new_door->state = DOOR_CLOSED;
	new_door->sprite = NULL;
	new_door->next = NULL;
	if (!game->doors)
		game->doors = new_door;
	else
	{
		current = game->doors;
		while (current->next)
			current = current->next;
		current->next = new_door;
	}
}

/* Helper: Remove door from map grid (replace P/B/C with '0') */
void	remove_door_from_map(t_game *game, int x, int y)
{
	if (y >= 0 && y < game->map.height && x >= 0
		&& x < (int)ft_strlen(game->map.grid[y]))
		game->map.grid[y][x] = '0';
}

/* Initialize door system - scan map for P, B, C and create door list */
void	init_doors_bonus(t_game *game)
{
	int		y;
	int		x;
	char	cell;

	game->doors = NULL;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			cell = game->map.grid[y][x];
			if (is_door_char(cell))
				add_door_to_list(game, x, y);
			x++;
		}
		y++;
	}
}

/* Free all doors in the list */
void	free_doors_bonus(t_game *game)
{
	t_door	*current;
	t_door	*next;

	current = game->doors;
	while (current)
	{
		next = current->next;
		if (current->sprite)
			mlx_destroy_image(game->mlx, current->sprite);
		free(current);
		current = next;
	}
	game->doors = NULL;
}
