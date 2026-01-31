/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 01:37:18 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap_bonus.h"

static void	put_pixel_minimap(t_game *game, int x, int y, int color)
{
	char	*pixel_addr;

	if (x < 0 || x >= LENGHT || y < 0 || y >= HEIGHT)
		return ;
	pixel_addr = game->img_addr.addr + (y * game->img_addr.line_lenght
			+ x * (game->img_addr.bpp / 8));
	*(unsigned int *)pixel_addr = color;
}

static void	draw_square(t_game *game, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_minimap(game, x + j, y + i, color);
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
	int	screen_x;
	int	screen_y;
	int	color;

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
	draw_square(game, screen_x, screen_y, mm->tile_size, color);
}

static void	draw_player_on_minimap(t_game *game, t_minimap *mm)
{
	int		screen_x;
	int		screen_y;
	int		i;
	int		j;
	double	angle;
	int		dir_x;
	int		dir_y;

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
}
