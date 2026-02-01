/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pokemon_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 09:54:38 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	load_pikachu_frames(t_game *game, t_pokemon *poke)
{
	char	path[256];
	char	*delays[] = {"0.17s", "0.1s", "0.13s", "0.17s", "0.03s", "0.47s",
		"0.1s", "0.03s", "0.07s", "0.13s", "0.4s", "0.07s", "0.1s", "0.03s", 
		"0.07s", "0.1s", "0.1s", "0.03s", "0.1s", "0.07s", "1s", "0.13s",
		"0.1s", "0.17s", "0.13s", "0.07s", "0.43s", "0.1s", "0.07s", "0.03s",
		"0.17s", "0.13s"};
	int		i;

	i = 0;
	while (i < PIKACHU_FRAMES)
	{
		snprintf(path, sizeof(path),
			"./assets/sprites/pokemon/pikachu/frame_%02d_delay-%s.xpm", i, delays[i]);
		poke->pikachu_frames[i].img = mlx_xpm_file_to_image(game->mlx, path,
				&poke->pikachu_frames[i].width,
				&poke->pikachu_frames[i].height);
		if (poke->pikachu_frames[i].img)
			poke->pikachu_frames[i].addr = mlx_get_data_addr(
					poke->pikachu_frames[i].img,
					&poke->pikachu_frames[i].bpp,
					&poke->pikachu_frames[i].line_lenght,
					&poke->pikachu_frames[i].endian);
		i++;
	}
}

static void	load_snorlax_frames(t_game *game, t_pokemon *poke)
{
	char	path[256];
	int		i;

	i = 0;
	while (i < SNORLAX_FRAMES)
	{
		snprintf(path, sizeof(path),
			"./assets/sprites/pokemon/snorlax/frame_%02d_delay-0.1s.xpm", i);
		poke->snorlax_frames[i].img = mlx_xpm_file_to_image(game->mlx, path,
				&poke->snorlax_frames[i].width,
				&poke->snorlax_frames[i].height);
		if (poke->snorlax_frames[i].img)
			poke->snorlax_frames[i].addr = mlx_get_data_addr(
					poke->snorlax_frames[i].img,
					&poke->snorlax_frames[i].bpp,
					&poke->snorlax_frames[i].line_lenght,
					&poke->snorlax_frames[i].endian);
		i++;
	}
}

static void	load_charizard_frames(t_game *game, t_pokemon *poke)
{
	char	path[256];
	int		i;

	i = 0;
	while (i < CHARIZARD_FRAMES)
	{
		snprintf(path, sizeof(path),
			"./assets/sprites/pokemon/charizard/frame_%02d_delay-0.1s.xpm",
			i);
		poke->charizard_frames[i].img = mlx_xpm_file_to_image(game->mlx, path,
				&poke->charizard_frames[i].width,
				&poke->charizard_frames[i].height);
		if (poke->charizard_frames[i].img)
			poke->charizard_frames[i].addr = mlx_get_data_addr(
					poke->charizard_frames[i].img,
					&poke->charizard_frames[i].bpp,
					&poke->charizard_frames[i].line_lenght,
					&poke->charizard_frames[i].endian);
		i++;
	}
}

/* Initialize Pokemon sprites for each door */
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

static void	draw_sprite_vertical_line(t_game *game, t_img *sprite, int x, int sprite_height, int draw_start_y, double sprite_x)
{
	int		y;
	int		d;
	int		tex_y;
	int		color;
	char	*pixel;

	y = draw_start_y;
	while (y < draw_start_y + sprite_height && y < HEIGHT)
	{
		if (y >= 0)
		{
			d = y * 256 - HEIGHT * 128 + sprite_height * 128;
			tex_y = ((d * sprite->height) / sprite_height) / 256;
			if (tex_y >= 0 && tex_y < sprite->height)
			{
				pixel = sprite->addr + (tex_y * sprite->line_lenght
						+ (int)sprite_x * (sprite->bpp / 8));
				color = *(unsigned int *)pixel;
			if ((color & 0x00FFFFFF) != 0x00FF00FF)
					*(unsigned int *)(game->img_addr.addr + (y
								* game->img_addr.line_lenght + x
								* (game->img_addr.bpp / 8))) = color;
			}
		}
		y++;
	}
}

static void	render_sprite(t_game *game, t_pokemon *pokemon, double sprite_x, double sprite_y)
{
	t_img	*current_sprite;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_start_x;
	int		draw_end_x;
	int		stripe;
	double	tex_x;

	if (pokemon->pokemon_type == POKEMON_PIKACHU)
		current_sprite = &pokemon->pikachu_frames[pokemon->current_frame];
	else if (pokemon->pokemon_type == POKEMON_SNORLAX)
		current_sprite = &pokemon->snorlax_frames[pokemon->current_frame];
	else if (pokemon->pokemon_type == POKEMON_CHARIZARD)
		current_sprite = &pokemon->charizard_frames[pokemon->current_frame];
	else
		current_sprite = (t_img *)pokemon->sprite;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	transform_x = inv_det * (game->player.dir_y * sprite_x
			- game->player.dir_x * sprite_y);
	transform_y = inv_det * (-game->player.plane_y * sprite_x
			+ game->player.plane_x * sprite_y);
	if (transform_y <= 0)
		return ;
	sprite_screen_x = (int)((LENGHT / 2) * (1 + transform_x / transform_y));
	sprite_height = abs((int)(HEIGHT / transform_y));
	sprite_width = abs((int)(HEIGHT / transform_y));
	draw_start_y = -sprite_height / 2 + HEIGHT / 2;
	draw_start_x = -sprite_width / 2 + sprite_screen_x;
	draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	if (draw_end_x >= LENGHT)
		draw_end_x = LENGHT - 1;
	stripe = draw_start_x;
	while (stripe < draw_end_x)
	{
		tex_x = (int)((stripe - (-sprite_width / 2 + sprite_screen_x))
				* current_sprite->width / sprite_width);
		if (transform_y > 0 && stripe >= 0 && stripe < LENGHT
			&& tex_x >= 0 && tex_x < current_sprite->width)
			draw_sprite_vertical_line(game, current_sprite, stripe,
				sprite_height, draw_start_y, tex_x);
		stripe++;
	}
}

/* Check if there's a wall between player and sprite */
static int	has_line_of_sight(t_game *game, double sprite_x, double sprite_y)
{
	double	dx = sprite_x + 0.5 - game->player.x;
	double	dy = sprite_y + 0.5 - game->player.y;
	double	distance = sqrt(dx * dx + dy * dy);
	double	step_size = 0.1;
	double	step_x = (dx / distance) * step_size;
	double	step_y = (dy / distance) * step_size;
	double	check_x = game->player.x;
	double	check_y = game->player.y;
	int		steps = (int)(distance / step_size);
	int		i;

	i = 0;
	while (i < steps)
	{
		check_x += step_x;
		check_y += step_y;
		if (check_x < 0 || check_y < 0 || 
			(int)check_x >= game->map.width || (int)check_y >= game->map.height)
			return (0);
		if (game->map.grid[(int)check_y][(int)check_x] == '1')
			return (0);
		i++;
	}
	return (1);
}

/* Draw Pokemon sprites using sprite casting */
void	draw_pokemon_bonus(t_game *game)
{
	t_pokemon	*current;
	double		sprite_x;
	double		sprite_y;

	current = game->pokemons;
	while (current)
	{
		if (current->active)
		{
			sprite_x = current->map_x + 0.5 - game->player.x;
			sprite_y = current->map_y + 0.5 - game->player.y;
			
			/* Only render if there's line of sight */
			if (has_line_of_sight(game, current->map_x, current->map_y))
				render_sprite(game, current, sprite_x, sprite_y);
		}
		current = current->next;
	}
}

/* Free all Pokemon sprites */
void	free_pokemon_bonus(t_game *game)
{
	t_pokemon	*current;
	t_pokemon	*next;
	int			i;

	current = game->pokemons;
	while (current)
	{
		next = current->next;
		if (current->sprite)
			mlx_destroy_image(game->mlx, current->sprite);
		if (current->pokemon_type == POKEMON_PIKACHU)
		{
			i = 0;
			while (i < PIKACHU_FRAMES)
			{
				if (current->pikachu_frames[i].img)
					mlx_destroy_image(game->mlx,
						current->pikachu_frames[i].img);
				i++;
			}
		}
		else if (current->pokemon_type == POKEMON_SNORLAX)
		{
			i = 0;
			while (i < SNORLAX_FRAMES)
			{
				if (current->snorlax_frames[i].img)
					mlx_destroy_image(game->mlx,
						current->snorlax_frames[i].img);
				i++;
			}
		}
		else if (current->pokemon_type == POKEMON_CHARIZARD)
		{
			i = 0;
			while (i < CHARIZARD_FRAMES)
			{
				if (current->charizard_frames[i].img)
					mlx_destroy_image(game->mlx,
						current->charizard_frames[i].img);
				i++;
			}
		}
		free(current);
		current = next;
	}
	game->pokemons = NULL;
}
