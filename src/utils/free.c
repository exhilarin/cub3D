/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:54:45 by agedikog          #+#    #+#             */
/*   Updated: 2026/01/24 16:49:38 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_game(t_game *game)
{
	if (game->textures.north)
		free(game->textures.north);
	if (game->textures.south)
		free(game->textures.south);
	if (game->textures.west)
		free(game->textures.west);
	if (game->textures.east)
		free(game->textures.east);
	if (game->map.grid)
		free_split(game->map.grid);
	if (game->map_fd >= 0)
		close(game->map_fd);
	free_mlx(game);
}

void free_mlx(t_game *game)
{
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->image)
        mlx_destroy_image(game->mlx, game->image);
    if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}