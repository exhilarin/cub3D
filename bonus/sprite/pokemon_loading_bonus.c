/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pokemon_loading_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 11:30:00 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	load_pikachu_frames(t_game *game, t_pokemon *poke)
{
	char	path[256];
	char	*delays[] = {"0.17s", "0.1s", "0.13s", "0.17s", "0.03s", "0.47s",
		"0.1s", "0.03s", "0.07s", "0.13s", "0.4s", "0.07s", "0.1s", "0.03s", 
		"0.07s", "0.1s", "0.1s", "0.03s", "0.1s", "0.07s", "1s", "0.13s",
		"0.1s", "0.17s", "0.13s", "0.07s", "0.43s", "0.1s", "0.07s", "0.03s",
		"0.17s", "0.13s"};
	int		i;

	i = 0;
	while (i < PIKACHU_FRAMES)
	{
		snprintf(path, sizeof(path),
			"./assets/sprites/pokemon/pikachu/frame_%02d_delay-%s.xpm", i, delays[i]);
		poke->pikachu_frames[i].img = mlx_xpm_file_to_image(game->mlx, path,
				&poke->pikachu_frames[i].width,
				&poke->pikachu_frames[i].height);
		if (poke->pikachu_frames[i].img)
			poke->pikachu_frames[i].addr = mlx_get_data_addr(
					poke->pikachu_frames[i].img,
					&poke->pikachu_frames[i].bpp,
					&poke->pikachu_frames[i].line_lenght,
					&poke->pikachu_frames[i].endian);
		i++;
	}
}

void	load_snorlax_frames(t_game *game, t_pokemon *poke)
{
	char	path[256];
	int		i;

	i = 0;
	while (i < SNORLAX_FRAMES)
	{
		snprintf(path, sizeof(path),
			"./assets/sprites/pokemon/snorlax/frame_%02d_delay-0.1s.xpm", i);
		poke->snorlax_frames[i].img = mlx_xpm_file_to_image(game->mlx, path,
				&poke->snorlax_frames[i].width,
				&poke->snorlax_frames[i].height);
		if (poke->snorlax_frames[i].img)
			poke->snorlax_frames[i].addr = mlx_get_data_addr(
					poke->snorlax_frames[i].img,
					&poke->snorlax_frames[i].bpp,
					&poke->snorlax_frames[i].line_lenght,
					&poke->snorlax_frames[i].endian);
		i++;
	}
}

void	load_charizard_frames(t_game *game, t_pokemon *poke)
{
	char	path[256];
	int		i;

	i = 0;
	while (i < CHARIZARD_FRAMES)
	{
		snprintf(path, sizeof(path),
			"./assets/sprites/pokemon/charizard/frame_%02d_delay-0.1s.xpm",
			i);
		poke->charizard_frames[i].img = mlx_xpm_file_to_image(game->mlx, path,
				&poke->charizard_frames[i].width,
				&poke->charizard_frames[i].height);
		if (poke->charizard_frames[i].img)
			poke->charizard_frames[i].addr = mlx_get_data_addr(
					poke->charizard_frames[i].img,
					&poke->charizard_frames[i].bpp,
					&poke->charizard_frames[i].line_lenght,
					&poke->charizard_frames[i].endian);
		i++;
	}
}