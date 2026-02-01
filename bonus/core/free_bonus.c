/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 02:25:14 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/* Free bonus-specific resources (doors, pokemon, animations) */
void	free_bonus_resources(t_game *game)
{
	free_doors_bonus(game);
	free_pokemon_bonus(game);
	if (game->anim.pokeball_img)
		mlx_destroy_image(game->mlx, game->anim.pokeball_img);
	if (game->anim.explosion_img)
		mlx_destroy_image(game->mlx, game->anim.explosion_img);
}
