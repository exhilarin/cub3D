/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agedikog <agedikog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:54:00 by agedikog          #+#    #+#             */
/*   Updated: 2025/12/21 15:54:02 by agedikog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void init_game(t_game *game)
{
    game->mlx = NULL;
    game->win = NULL;
    game->map_fd = -1;
    game->map_path = NULL;
}

static void init_texture(t_texture *texture)
{
    texture->north = NULL;
    texture->south = NULL;
    texture->west = NULL;
    texture->east = NULL;
    texture->floor_color = -1;
    texture->ceiling_color = -1;
    texture->c_count = 0;
}

static void init_map(t_map *map)
{
    map->grid = NULL;
    map->width = 0;
    map->height = 0;
    map->player_count = 0;
    map->player_dir = '\0';
    map->player_x = 0.0;
    map->player_y = 0.0;
}

void init_data(t_game *game)
{
    init_game(game);
    init_texture(&game->textures);
    init_map(&game->map);
}
