/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 03:59:08 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

/* Initialize animation system */
void	init_animations_bonus(t_game *game)
{
	game->anim.type = ANIM_NONE;
	game->anim.frame_count = 0;
	game->anim.map_x = 0;
	game->anim.map_y = 0;
	game->anim.pokeball_img = NULL;
	game->anim.explosion_img = NULL;
	game->pokeball_hud.img = mlx_xpm_file_to_image(game->mlx,
			"./assets/pokeball_01.xpm",
			&game->pokeball_hud.width, &game->pokeball_hud.height);
	if (game->pokeball_hud.img)
		game->pokeball_hud.addr = mlx_get_data_addr(game->pokeball_hud.img,
				&game->pokeball_hud.bpp, &game->pokeball_hud.line_lenght,
				&game->pokeball_hud.endian);
}

/* Update animations - advance frame counters */
void	update_animations_bonus(t_game *game)
{
	if (game->anim.type == ANIM_POKEBALL)
	{
		game->anim.frame_count++;
		if (game->anim.frame_count >= POKEBALL_ANIM_FRAMES)
		{
			game->anim.type = ANIM_EXPLOSION;
			game->anim.frame_count = 0;
		}
	}
	else if (game->anim.type == ANIM_EXPLOSION)
	{
		game->anim.frame_count++;
		if (game->anim.frame_count >= EXPLOSION_FRAMES)
		{
			game->anim.type = ANIM_NONE;
			game->anim.frame_count = 0;
		}
	}
}

/* Draw Pokeball animation in player's hand (HUD overlay) */
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

/* Draw transparent image (skip black/transparent pixels) */
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

/* Draw explosion effect at door location (simple expanding circle) */
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
