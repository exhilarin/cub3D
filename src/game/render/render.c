/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/01/27 01:55:52 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_floor_ceiling(t_game *game)
{
	unsigned int	color;
	char			*pixel_addr;
	int				x;
	int				y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < HEIGHT / 2)
			color = game->textures.ceiling_color;
		else
			color = game->textures.floor_color;
		x = 0;
		while (x < LENGHT)
		{
			pixel_addr = game->img_addr.addr + (y
					* game->img_addr.line_lenght + x
					* (game->img_addr.bpp / 8));
			*(unsigned int *)pixel_addr = color;
			x++;
		}
		y++;
	}
}

void	render_frame(t_game *game)
{
	update_player(game);
	draw_floor_ceiling(game);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image, 0, 0);
}
