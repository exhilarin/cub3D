/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/02 17:49:11 by ilyas-guney      ###   ########.fr       */
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
	game->anim.type = ANIM_NONE;
	game->anim.frame_count = 0;
	game->anim.map_x = 0;
	game->anim.map_y = 0;
	game->anim.pokeball_img = NULL;
	game->pokeball_hud.img = mlx_xpm_file_to_image(game->mlx,
			"./assets/sprites/pokeball/frame_0_delay-0.2s.xpm",
			&game->pokeball_hud.width, &game->pokeball_hud.height);
	if (game->pokeball_hud.img)
		game->pokeball_hud.addr = mlx_get_data_addr(game->pokeball_hud.img,
				&game->pokeball_hud.bpp, &game->pokeball_hud.line_lenght,
				&game->pokeball_hud.endian);
	load_hand_frames(game);
}

void	update_animations_bonus(t_game *game)
{
	if (game->anim.type == ANIM_POKEBALL)
	{
		game->anim.frame_count++;
		if (game->anim.frame_count >= POKEBALL_ANIM_FRAMES)
		{
			game->anim.type = ANIM_NONE;
			game->anim.frame_count = 0;
		}
	}
}

void	draw_pokeball_animation(t_game *game)
{
	int		hud_x;
	int		hud_y;
	int		offset;

	if (game->anim.type != ANIM_POKEBALL)
		return ;
	hud_x = LENGHT - 150;
	hud_y = HEIGHT - 150;
	offset = game->anim.frame_count * 2;
	hud_y -= offset;
	if (game->anim.pokeball_img)
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->anim.pokeball_img, hud_x, hud_y);
	}
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

void	draw_scaled_transparent_image(t_game *game, t_img *img_data,
		int x, int y, float scale)
{
	int		i;
	int		j;
	int		color;
	char	*pixel;
	char	*dst;
	int		scaled_w;
	int		scaled_h;

	if (!img_data || !img_data->img || !img_data->addr)
		return ;
	scaled_w = (int)(img_data->width * scale);
	scaled_h = (int)(img_data->height * scale);
	i = 0;
	while (i < scaled_h)
	{
		j = 0;
		while (j < scaled_w)
		{
			pixel = img_data->addr + ((int)(i / scale) * img_data->line_lenght
					+ (int)(j / scale) * (img_data->bpp / 8));
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

