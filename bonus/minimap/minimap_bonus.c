/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 10:23:10 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

typedef struct s_square
{
	int	x;
	int	y;
	int	size;
	int	color;
}	t_square;

static void	put_pixel_minimap(t_game *game, int x, int y, int color)
{
	char	*pixel_addr;

	if (x < 0 || x >= LENGHT || y < 0 || y >= HEIGHT)
		return ;
	pixel_addr = game->img_addr.addr + (y * game->img_addr.line_lenght
			+ x * (game->img_addr.bpp / 8));
	*(unsigned int *)pixel_addr = color;
}

static void	draw_square(t_game *game, t_square *sq)
{
	int	i;
	int	j;

	i = 0;
	while (i < sq->size)
	{
		j = 0;
		while (j < sq->size)
		{
			put_pixel_minimap(game, sq->x + j, sq->y + i, sq->color);
			j++;
		}
		i++;
	}
}

static int	is_outer_wall(t_game *game, int mx, int my)
{
	if (game->map.grid[my][mx] != '1')
		return (0);
	if (my == 0 || my == game->map.height - 1)
		return (1);
	if (mx == 0 || mx == (int)ft_strlen(game->map.grid[my]) - 1)
		return (1);
	return (0);
}

static void	draw_minimap_tile(t_game *game, t_minimap *mm, int mx, int my)
{
	int			screen_x;
	int			screen_y;
	int			color;
	t_square	sq;

	if (mx < 0 || mx >= game->map.width || my < 0 || my >= game->map.height)
		return ;
	if (mx >= (int)ft_strlen(game->map.grid[my]))
		return ;
	if (game->map.grid[my][mx] == ' ' || game->map.grid[my][mx] == '\0')
		return ;
	screen_x = mm->offset_x + (mx * mm->tile_size);
	screen_y = mm->offset_y + (my * mm->tile_size);
	if (is_outer_wall(game, mx, my))
		color = MINIMAP_BORDER_COLOR;
	else if (game->map.grid[my][mx] == '1')
		color = MINIMAP_WALL_COLOR;
	else
		color = MINIMAP_BG_COLOR;
	sq.x = screen_x;
	sq.y = screen_y;
	sq.size = mm->tile_size;
	sq.color = color;
	draw_square(game, &sq);
}

static void	draw_player_square(t_game *game, t_minimap *mm)
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

static void	draw_player_direction(t_game *game, t_minimap *mm)
{
	double	angle;
	int		dir_x;
	int		dir_y;
	int		i;

	angle = atan2(game->player.dir_y, game->player.dir_x);
	dir_x = (int)(cos(angle) * (MINIMAP_PLAYER_SIZE + 2));
	dir_y = (int)(sin(angle) * (MINIMAP_PLAYER_SIZE + 2));
	i = 0;
	while (i < MINIMAP_PLAYER_SIZE + 2)
	{
		put_pixel_minimap(game, mm->player_x + (dir_x * i)
			/ (MINIMAP_PLAYER_SIZE + 2), mm->player_y + (dir_y * i)
			/ (MINIMAP_PLAYER_SIZE + 2), MINIMAP_PLAYER_COLOR);
		i++;
	}
}

static void	draw_player_on_minimap(t_game *game, t_minimap *mm)
{
	draw_player_square(game, mm);
	draw_player_direction(game, mm);
}

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

void	draw_pokemon_on_minimap(t_game *game, t_minimap *minimap)
{
	t_door		*current_door;
	t_pokemon	*current_pokemon;
	int			pokemon_color;

	/* Draw doors that haven't been opened */
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

	/* Draw active Pokemon that haven't been collected */
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
	minimap->player_x = minimap->offset_x
		+ (int)(game->player.x * minimap->tile_size);
	minimap->player_y = minimap->offset_y
		+ (int)(game->player.y * minimap->tile_size);
}

void	draw_minimap(t_game *game, t_minimap *minimap)
{
	int	mx;
	int	my;

	if (!minimap)
		return ;
	minimap->player_x = minimap->offset_x
		+ (int)(game->player.x * minimap->tile_size);
	minimap->player_y = minimap->offset_y
		+ (int)(game->player.y * minimap->tile_size);
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
	minimap->player_x = minimap->offset_x
		+ (int)(game->player.x * minimap->tile_size);
	minimap->player_y = minimap->offset_y
		+ (int)(game->player.y * minimap->tile_size);
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
