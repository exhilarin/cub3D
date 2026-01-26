/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/01/27 01:08:30 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_game *game, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		free_game(game);
		ft_perror("Error\nFailed to load texture\n");
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_lenght, &texture->endian);
	if (!texture->addr)
	{
		free_game(game);
		ft_perror("Error\nFailed to get texture data\n");
	}
}

void	load_textures(t_game *game)
{
	load_texture(game, &game->textures.no, game->textures.north);
	load_texture(game, &game->textures.so, game->textures.south);
	load_texture(game, &game->textures.we, game->textures.west);
	load_texture(game, &game->textures.ea, game->textures.east);
}

void	init_mlx_display(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free_game(game);
		ft_perror("Error\nFailed to initialize MLX\n");
	}
	game->win = mlx_new_window(game->mlx, LENGHT, HEIGHT, "cub3D");
	if (!game->win)
	{
		free_game(game);
		ft_perror("Error\nFailed to create window\n");
	}
}

void	init_mlx_image(t_game *game)
{
	game->image = mlx_new_image(game->mlx, LENGHT, HEIGHT);
	if (!game->image)
	{
		free_game(game);
		ft_perror("Error\nFailed to create image\n");
	}
	game->img_addr.addr = mlx_get_data_addr(game->image,
			&game->img_addr.bpp, &game->img_addr.line_lenght,
			&game->img_addr.endian);
	if (!game->img_addr.addr)
	{
		free_game(game);
		ft_perror("Error\nFailed to get image data\n");
	}
}

void	init_mlx(t_game *game)
{
	init_mlx_display(game);
	init_mlx_image(game);
	load_textures(game);
}
