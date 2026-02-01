/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_drawing_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 11:00:00 by ilyas-guney      ###   ########.fr       */
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

void	put_pixel_minimap(t_game *game, int x, int y, int color)
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

int	is_outer_wall(t_game *game, int mx, int my)
{
	if (mx == 0 || my == 0 || mx == game->map.width - 1
		|| my == game->map.height - 1)
		return (game->map.grid[my][mx] == '1');
	return (0);
}

void	draw_minimap_tile(t_game *game, t_minimap *mm, int mx, int my)
{
	int			screen_x;
	int			screen_y;
	int			color;
	t_square	square;

	screen_x = mm->offset_x + (mx * mm->tile_size);
	screen_y = mm->offset_y + (my * mm->tile_size);
	if (game->map.grid[my][mx] == '1')
	{
		if (is_outer_wall(game, mx, my))
			color = MINIMAP_BORDER_COLOR;
		else
			color = MINIMAP_WALL_COLOR;
	}
	else if (game->map.grid[my][mx] == '0'
		|| ft_strchr("NSEW", game->map.grid[my][mx]))
		color = MINIMAP_BG_COLOR;
	else
		color = MINIMAP_BG_COLOR;
	square.x = screen_x;
	square.y = screen_y;
	square.size = mm->tile_size;
	square.color = color;
	draw_square(game, &square);
}