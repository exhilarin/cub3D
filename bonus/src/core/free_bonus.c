/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/02 16:33:55 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	free_bonus_resources(t_game *game)
{
	int	i;

	free_doors_bonus(game);
	free_pokemon_bonus(game);
	if (game->anim.pokeball_img)
	{
		mlx_destroy_image(game->mlx, game->anim.pokeball_img);
		game->anim.pokeball_img = NULL;
	}
	if (game->pokeball_hud.img)
	{
		mlx_destroy_image(game->mlx, game->pokeball_hud.img);
		game->pokeball_hud.img = NULL;
	}
	i = 0;
	while (i < HAND_FRAMES)
	{
		if (game->hand_frames[i].img)
			mlx_destroy_image(game->mlx, game->hand_frames[i].img);
		i++;
	}
	if (game->textures.grass.img)
	{
		mlx_destroy_image(game->mlx, game->textures.grass.img);
		game->textures.grass.img = NULL;
	}
}
