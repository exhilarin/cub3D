/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/02 02:17:16 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

typedef struct s_explosion_draw
{
	int	screen_x;
	int	screen_y;
	int	radius;
	int	color;
}	t_explosion_draw;

typedef struct s_pixel_pos
{
	int	i;
	int	j;
}	t_pixel_pos;

void	init_animations_bonus(t_game *game)
{
	int		i;

	game->anim.type = ANIM_NONE;
	game->anim.frame_count = 0;
	game->anim.map_x = 0;
	game->anim.map_y = 0;
	game->anim.current_pokeball_frame = 0;
	game->anim.pokeball_img = NULL;
	i = 0;
	while (i < POKEBALL_FRAMES)
	{
		game->anim.pokeball_frames[i].img = NULL;
		i++;
	}
	game->pokeball_hud.img = mlx_xpm_file_to_image(game->mlx,
		"./assets/sprites/pokeball/pokeball_01.xpm",
		&game->pokeball_hud.width, &game->pokeball_hud.height);
	if (game->pokeball_hud.img)
		game->pokeball_hud.addr = mlx_get_data_addr(game->pokeball_hud.img,
			&game->pokeball_hud.bpp, &game->pokeball_hud.line_lenght,
			&game->pokeball_hud.endian);
}

void	update_animations_bonus(t_game *game)
{
	if (game->anim.type == ANIM_POKEBALL)
	{
		game->anim.frame_count++;
		if (game->anim.frame_count % 5 == 0)
			game->anim.current_pokeball_frame++;
		if (game->anim.frame_count >= POKEBALL_ANIM_FRAMES)
		{
			game->anim.type = ANIM_NONE;
			game->anim.frame_count = 0;
			game->anim.current_pokeball_frame = 0;
		}
	}
}

static void	calculate_sprite_transform(t_game *game, double *transforms)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = game->anim.map_x + 0.5 - game->player.x;
	sprite_y = game->anim.map_y + 0.5 - game->player.y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	transforms[0] = inv_det * (game->player.dir_y * sprite_x
			- game->player.dir_x * sprite_y);
	transforms[1] = inv_det * (-game->player.plane_y * sprite_x
			+ game->player.plane_x * sprite_y);
}

static void	draw_animation_stripe(t_game *game, t_img *frame,
	int sprite_height, int *draw_params)
{
	int		y;
	int		d;
	int		tex_y;
	int		color;
	char	*pixel;
	int		*buffer;

	y = draw_params[2];
	buffer = (int *)game->img_addr.addr;
	while (y < draw_params[2] + sprite_height && y < HEIGHT)
	{
		if (y >= 0)
		{
			d = y * 256 - HEIGHT * 128 + sprite_height * 128;
			tex_y = ((d * frame->height) / sprite_height) / 256;
			if (tex_y >= 0 && tex_y < frame->height)
			{
				pixel = frame->addr + (tex_y * frame->line_lenght
						+ (int)draw_params[3] * (frame->bpp / 8));
				color = *(unsigned int *)pixel;
				if ((color & 0x00FFFFFF) != 0x00FF00FF && (color & 0x00FFFFFF) != 0)
					buffer[y * LENGHT + draw_params[0]] = color;
			}
		}
		y++;
	}
}

static void	render_animation_frame(t_game *game, t_img *frame,
	double *transforms, int *screen_params)
{
	int		stripe;
	double	tex_x;
	int		draw_params[4];

	stripe = screen_params[2];
	while (stripe < screen_params[3])
	{
		tex_x = (int)((stripe - screen_params[2])
				* frame->width / screen_params[1]);
		if (transforms[1] > 0 && stripe >= 0 && stripe < LENGHT
			&& tex_x >= 0 && tex_x < frame->width)
		{
			draw_params[0] = stripe;
			draw_params[2] = screen_params[4];
			draw_params[3] = (int)tex_x;
			draw_animation_stripe(game, frame, screen_params[0], draw_params);
		}
		stripe++;
	}
}

void	draw_pokeball_animation(t_game *game)
{
	double	transforms[2];
	int		screen_params[5];
	t_img	*frame;

	if (game->anim.type != ANIM_POKEBALL)
		return ;
	if (game->anim.current_pokeball_frame < 0
		|| game->anim.current_pokeball_frame >= POKEBALL_FRAMES)
		return ;
	frame = &game->anim.pokeball_frames[game->anim.current_pokeball_frame];
	if (!frame->img)
		return ;
	calculate_sprite_transform(game, transforms);
	if (transforms[1] <= 0)
		return ;
	screen_params[0] = abs((int)(HEIGHT / transforms[1]));
	screen_params[1] = screen_params[0];
	screen_params[2] = -screen_params[1] / 2
		+ (int)((LENGHT / 2) * (1 + transforms[0] / transforms[1]));
	screen_params[3] = screen_params[1] / 2
		+ (int)((LENGHT / 2) * (1 + transforms[0] / transforms[1]));
	screen_params[4] = -screen_params[0] / 2 + HEIGHT / 2;
	render_animation_frame(game, frame, transforms, screen_params);
}

static void	put_explosion_pixel(t_game *game, t_explosion_draw *ex, 
							t_pixel_pos *pos)
{
	char	*pixel;

	if (ex->screen_x + pos->j < 0 || ex->screen_x + pos->j >= LENGHT)
		return ;
	if (ex->screen_y + pos->i < 0 || ex->screen_y + pos->i >= HEIGHT)
		return ;
	pixel = game->img_addr.addr
		+ ((ex->screen_y + pos->i) * game->img_addr.line_lenght
		+ (ex->screen_x + pos->j) * (game->img_addr.bpp / 8));
	*(unsigned int *)pixel = ex->color;
}

static void	draw_explosion_circle(t_game *game, t_explosion_draw *ex)
{
	t_pixel_pos	pos;

	pos.i = -ex->radius;
	while (pos.i <= ex->radius)
	{
		pos.j = -ex->radius;
		while (pos.j <= ex->radius)
		{
			if (pos.i * pos.i + pos.j * pos.j <= ex->radius * ex->radius)
				put_explosion_pixel(game, ex, &pos);
			pos.j++;
		}
		pos.i++;
	}
}

void	draw_transparent_image(t_game *game, t_img *img_data, int x, int y)
{
	int		i;
	int		j;
	int		color;
	char	*pixel;
	char	*dst;

	if (!img_data || !img_data->img || !img_data->addr)
		return ;
	i = 0;
	while (i < img_data->height)
	{
		j = 0;
		while (j < img_data->width)
		{
			pixel = img_data->addr + (i * img_data->line_lenght
					+ j * (img_data->bpp / 8));
			color = *(unsigned int *)pixel;
			if ((color & 0x00FFFFFF) != 0x00000000)
			{
				if (y + i >= 0 && y + i < HEIGHT
					&& x + j >= 0 && x + j < LENGHT)
				{
					dst = game->img_addr.addr + ((y + i)
							* game->img_addr.line_lenght + (x + j)
							* (game->img_addr.bpp / 8));
					*(unsigned int *)dst = color;
				}
			}
			j++;
		}
		i++;
	}
}

void	draw_explosion_animation(t_game *game)
{
	t_explosion_draw	ex;

	if (game->anim.type != ANIM_EXPLOSION)
		return ;
	ex.screen_x = LENGHT / 2;
	ex.screen_y = HEIGHT / 2;
	ex.radius = game->anim.frame_count * 5;
	ex.color = 0xFF6600 - (game->anim.frame_count * 10 << 16);
	draw_explosion_circle(game, &ex);
}
