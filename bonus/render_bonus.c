/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 01:37:18 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "minimap_bonus.h"

static void	draw_floor_ceiling_bonus(t_game *game)
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

void	render_frame_bonus(t_game *game)
{
	update_player_speed_bonus(game);
	update_player_bonus(game);
	draw_floor_ceiling_bonus(game);
	draw_walls(game);
	draw_minimap_with_border(game, &game->minimap);
	mlx_put_image_to_window(game->mlx, game->win, game->image, 0, 0);
}
