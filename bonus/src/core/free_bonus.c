/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 22:48:48 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	free_bonus_resources(t_game *game)
{
	int	i;

	free_doors_bonus(game);
	free_pokemon_bonus(game);
	if (game->anim.pokeball_img)
		mlx_destroy_image(game->mlx, game->anim.pokeball_img);
	i = 0;
	while (i < POKEBALL_FRAMES)
	{
		if (game->anim.pokeball_frames[i].img)
			mlx_destroy_image(game->mlx, game->anim.pokeball_frames[i].img);
		i++;
	}
}
