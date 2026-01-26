/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:54:00 by agedikog          #+#    #+#             */
/*   Updated: 2026/01/27 01:00:25 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->image = NULL;
	game->addres = NULL;
	game->map_fd = -1;
	game->map_path = NULL;
	game->img_addr.addr = NULL;
	game->img_addr.bpp = 0;
	game->img_addr.line_lenght = 0;
	game->img_addr.endian = 0;
}

static void	init_texture_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->width = 0;
	img->height = 0;
	img->bpp = 0;
	img->line_lenght = 0;
	img->endian = 0;
}

static void	init_texture(t_texture *texture)
{
	texture->north = NULL;
	texture->south = NULL;
	texture->west = NULL;
	texture->east = NULL;
	texture->floor_color = -1;
	texture->ceiling_color = -1;
	texture->c_count = 0;
	init_texture_img(&texture->no);
	init_texture_img(&texture->so);
	init_texture_img(&texture->we);
	init_texture_img(&texture->ea);
}

static void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->player_count = 0;
	map->player_dir = '\0';
	map->player_x = 0.0;
	map->player_y = 0.0;
}

void	init_data(t_game *game)
{
	init_game(game);
	init_texture(&game->textures);
	init_map(&game->map);
}
