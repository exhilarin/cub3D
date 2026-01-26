/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/01/27 01:55:53 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_game *game, int x, int y, int tex_y)
{
	unsigned int	color;
	char			*dst;

	dst = game->img_addr.addr + (y * game->img_addr.line_lenght
			+ x * (game->img_addr.bpp / 8));
	color = *(unsigned int *)(game->tex.img->addr
			+ (tex_y * game->tex.img->line_lenght
				+ game->tex.tex_x * (game->tex.img->bpp / 8)));
	*(unsigned int *)dst = color;
}
