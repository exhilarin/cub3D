/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/02 17:49:11 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"
#include <string.h>

typedef struct s_floor
{
	double	ray_dir_x0;
	double	ray_dir_y0;
	double	ray_dir_x1;
	double	ray_dir_y1;
	double	pos_z;
	double	row_distance;
	double	floor_step_x;
	double	floor_step_y;
	double	floor_x;
	double	floor_y;
	int		tex_width;
	int		tex_height;
}	t_floor;

static void	init_floor_casting(t_game *game, t_floor *f)
{
	f->ray_dir_x0 = game->player.dir_x - game->player.plane_x;
	f->ray_dir_y0 = game->player.dir_y - game->player.plane_y;
	f->ray_dir_x1 = game->player.dir_x + game->player.plane_x;
	f->ray_dir_y1 = game->player.dir_y + game->player.plane_y;
	f->pos_z = 0.5 * HEIGHT;
	f->tex_width = game->textures.grass.width;
	f->tex_height = game->textures.grass.height;
}

static void	draw_floor_row(t_game *game, t_floor *f, int y)
{
	unsigned int	*dst;
	char			*src_base;
	int				x;
	int				tex_x;
	int				tex_y;
	int				line_offset;

	dst = (unsigned int *)(game->img_addr.addr
			+ y * game->img_addr.line_lenght);
	src_base = game->textures.grass.addr;
	line_offset = game->textures.grass.line_lenght;
	x = -1;
	while (++x < LENGHT)
	{
		tex_x = (int)(f->floor_x * f->tex_width) % f->tex_width;
		tex_y = (int)(f->floor_y * f->tex_height) % f->tex_height;
		if (tex_x < 0)
			tex_x += f->tex_width;
		if (tex_y < 0)
			tex_y += f->tex_height;
		dst[x] = *(unsigned int *)(src_base + tex_y * line_offset
				+ tex_x * 4);
		f->floor_x += f->floor_step_x;
		f->floor_y += f->floor_step_y;
	}
}

static void	copy_floor_row(t_game *game, int src_y, int dst_y)
{
	unsigned int	*src;
	unsigned int	*dst;
	int				x;

	src = (unsigned int *)(game->img_addr.addr
			+ src_y * game->img_addr.line_lenght);
	dst = (unsigned int *)(game->img_addr.addr
			+ dst_y * game->img_addr.line_lenght);
	x = -1;
	while (++x < LENGHT)
		dst[x] = src[x];
}

static void	draw_ceiling_fast(t_game *game)
{
	unsigned int	*line;
	unsigned int	color;
	int				y;
	int				x;

	color = game->textures.ceiling_color;
	y = -1;
	while (++y < HEIGHT / 2)
	{
		line = (unsigned int *)(game->img_addr.addr
				+ y * game->img_addr.line_lenght);
		x = -1;
		while (++x < LENGHT)
			line[x] = color;
	}
}

void	draw_floor_ceiling_bonus(t_game *game)
{
	t_floor	f;
	int		y;
	int		p;

	draw_ceiling_fast(game);
	if (!game->textures.grass.addr)
		return ;
	init_floor_casting(game, &f);
	y = HEIGHT / 2;
	while (++y < HEIGHT)
	{
		p = y - HEIGHT / 2;
		f.row_distance = f.pos_z / p;
		f.floor_step_x = f.row_distance * (f.ray_dir_x1 - f.ray_dir_x0)
			/ LENGHT;
		f.floor_step_y = f.row_distance * (f.ray_dir_y1 - f.ray_dir_y0)
			/ LENGHT;
		f.floor_x = game->player.x + f.row_distance * f.ray_dir_x0;
		f.floor_y = game->player.y + f.row_distance * f.ray_dir_y0;
		draw_floor_row(game, &f, y);
		if (++y < HEIGHT)
			copy_floor_row(game, y - 1, y);
	}
}

void	render_frame_bonus(t_game *game)
{
	update_player_speed_bonus(game);
	update_player_bonus(game);
	update_doors_bonus(game);
	update_pokemon_bonus(game);
	update_animations_bonus(game);
	update_hand_animation(game);
	draw_floor_ceiling_bonus(game);
	draw_walls(game);
	draw_doors_bonus(game);
	draw_pokemon_bonus(game);
	draw_pokeball_animation(game);
	draw_explosion_animation(game);
	draw_minimap_with_border(game, &game->minimap);
	draw_hand_hud(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image, 0, 0);
}
