/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/01/27 01:55:53 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compute_ray(t_game *game, int x)
{
	game->ray.camera_x = 2.0 * x / (double)LENGHT - 1;
	game->ray.dir_x = game->player.dir_x
		+ game->player.plane_x * game->ray.camera_x;
	game->ray.dir_y = game->player.dir_y
		+ game->player.plane_y * game->ray.camera_x;
	game->ray.map_x = (int)game->player.x;
	game->ray.map_y = (int)game->player.y;
}

void	select_texture(t_game *game)
{
	if (game->dda.side == 0 && game->ray.dir_x > 0)
		game->tex.img = &game->textures.ea;
	else if (game->dda.side == 0 && game->ray.dir_x < 0)
		game->tex.img = &game->textures.we;
	else if (game->dda.side == 1 && game->ray.dir_y > 0)
		game->tex.img = &game->textures.so;
	else
		game->tex.img = &game->textures.no;
}

void	compute_texcoords(t_game *game)
{
	double	wall_x;

	if (game->dda.side == 0)
		wall_x = game->player.y + game->wall.perp_dist * game->ray.dir_y;
	else
		wall_x = game->player.x + game->wall.perp_dist * game->ray.dir_x;
	wall_x -= floor(wall_x);
	game->tex.tex_x = (int)(wall_x * (double)game->tex.img->width);
	if (game->tex.tex_x >= game->tex.img->width)
		game->tex.tex_x = game->tex.img->width - 1;
	if (game->tex.tex_x < 0)
		game->tex.tex_x = 0;
	game->tex.step = 1.0 * game->tex.img->height / game->wall.line_height;
	game->tex.tex_pos = (game->wall.draw_start - HEIGHT / 2
			+ game->wall.line_height / 2) * game->tex.step;
}

void	draw_vertical_stripe(t_game *game, int x)
{
	int				y;
	int				tex_y;

	if (!game->tex.img || !game->tex.img->addr)
		return ;
	y = game->wall.draw_start;
	while (y <= game->wall.draw_end)
	{
		if (y >= 0 && y < HEIGHT && x >= 0 && x < LENGHT)
		{
			tex_y = (int)game->tex.tex_pos & (game->tex.img->height - 1);
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= game->tex.img->height)
				tex_y = game->tex.img->height - 1;
			game->tex.tex_pos += game->tex.step;
			draw_pixel(game, x, y, tex_y);
		}
		y++;
	}
}

void	draw_walls(t_game *game)
{
	int	x;

	x = 0;
	while (x < LENGHT)
	{
		compute_ray(game, x);
		init_dda(game);
		perform_dda(game);
		compute_wall_params(game);
		select_texture(game);
		compute_texcoords(game);
		draw_vertical_stripe(game, x);
		x++;
	}
}
