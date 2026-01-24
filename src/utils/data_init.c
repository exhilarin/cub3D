/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:54:00 by agedikog          #+#    #+#             */
/*   Updated: 2026/01/24 16:48:08 by iguney           ###   ########.fr       */
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

static void	init_texture(t_texture *texture)
{
	texture->north = NULL;
	texture->south = NULL;
	texture->west = NULL;
	texture->east = NULL;
	texture->floor_color = -1;
	texture->ceiling_color = -1;
	texture->c_count = 0;
	
	texture->no.img = NULL;
	texture->no.addr = NULL;
	texture->no.width = 0;
	texture->no.height = 0;
	texture->no.bpp = 0;
	texture->no.line_lenght = 0;
	texture->no.endian = 0;
	
	texture->so.img = NULL;
	texture->so.addr = NULL;
	texture->so.width = 0;
	texture->so.height = 0;
	texture->so.bpp = 0;
	texture->so.line_lenght = 0;
	texture->so.endian = 0;
	
	texture->we.img = NULL;
	texture->we.addr = NULL;
	texture->we.width = 0;
	texture->we.height = 0;
	texture->we.bpp = 0;
	texture->we.line_lenght = 0;
	texture->we.endian = 0;
	
	texture->ea.img = NULL;
	texture->ea.addr = NULL;
	texture->ea.width = 0;
	texture->ea.height = 0;
	texture->ea.bpp = 0;
	texture->ea.line_lenght = 0;
	texture->ea.endian = 0;
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
