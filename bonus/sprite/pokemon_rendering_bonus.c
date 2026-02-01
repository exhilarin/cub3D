/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pokemon_rendering_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 11:30:00 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	blend_colors(int sprite_color, int bg_color, int alpha)
{
	int	r1, g1, b1;
	int	r2, g2, b2;
	int	r, g, b;

	r1 = (sprite_color >> 16) & 0xFF;
	g1 = (sprite_color >> 8) & 0xFF;
	b1 = sprite_color & 0xFF;
	r2 = (bg_color >> 16) & 0xFF;
	g2 = (bg_color >> 8) & 0xFF;
	b2 = bg_color & 0xFF;
	r = ((r1 * alpha) + (r2 * (MAX_ALPHA - alpha))) / MAX_ALPHA;
	g = ((g1 * alpha) + (g2 * (MAX_ALPHA - alpha))) / MAX_ALPHA;
	b = ((b1 * alpha) + (b2 * (MAX_ALPHA - alpha))) / MAX_ALPHA;
	return ((r << 16) | (g << 8) | b);
}

static void	draw_sprite_vertical_line(t_game *game, t_img *sprite, int x, 
	int sprite_height, int draw_start_y, double sprite_x, int alpha)
{
	int		y;
	int		d;
	int		tex_y;
	int		color;
	int		blended_color;
	char	*pixel;
	int		*buffer;

	y = draw_start_y;
	buffer = (int *)game->img_addr.addr;
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
				{
					if (alpha < MAX_ALPHA)
						blended_color = blend_colors(color,
							buffer[y * LENGHT + x], alpha);
					else
						blended_color = color;
					buffer[y * LENGHT + x] = blended_color;
				}
			}
		}
		y++;
	}
}

static void	render_sprite(t_game *game, t_pokemon *pokemon, 
	double sprite_x, double sprite_y)
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
					sprite_height, draw_start_y, tex_x, pokemon->alpha);
		stripe++;
	}
}

static int	has_line_of_sight(t_game *game, double sprite_x, double sprite_y)
{
	double	dx;
	double	dy;
	double	distance;
	double	step_size;
	double	step_x;
	double	step_y;
	double	check_x;
	double	check_y;
	int		steps;
	int		i;

	dx = sprite_x + 0.5 - game->player.x;
	dy = sprite_y + 0.5 - game->player.y;
	distance = sqrt(dx * dx + dy * dy);
	step_size = 0.1;
	step_x = (dx / distance) * step_size;
	step_y = (dy / distance) * step_size;
	check_x = game->player.x;
	check_y = game->player.y;
	steps = (int)(distance / step_size);
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

void	draw_pokemon_bonus(t_game *game)
{
	t_pokemon	*current;
	double		sprite_x;
	double		sprite_y;

	current = game->pokemons;
	while (current)
	{
		if ((current->active || current->fading > 0) && current->alpha > 0)
		{
			sprite_x = current->map_x + 0.5 - game->player.x;
			sprite_y = current->map_y + 0.5 - game->player.y;
			if (has_line_of_sight(game, current->map_x, current->map_y))
				render_sprite(game, current, sprite_x, sprite_y);
		}
		current = current->next;
	}
}