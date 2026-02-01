/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 03:13:41 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_BONUS_H
# define DOOR_BONUS_H

/* Sprite paths */
# define SPRITE_POKEBALL "./assets/sprites/effects/pokeball.xpm"
# define SPRITE_EXPLOSION "./assets/sprites/effects/explosion.xpm"
# define SPRITE_PIKACHU "./assets/sprites/pokemon/pikachu.xpm"
# define SPRITE_CHARMANDER "./assets/sprites/pokemon/charmander.xpm"
# define SPRITE_BULBASAUR "./assets/sprites/pokemon/bulbasaur.xpm"

/* Pokemon door characters */
# define DOOR_PIKACHU 'P'
# define DOOR_BULBASAUR 'B'
# define DOOR_CHARMANDER 'C'

/* Pokemon types */
# define POKEMON_PIKACHU 0
# define POKEMON_BULBASAUR 1
# define POKEMON_CHARMANDER 2

/* Door and Pokemon configuration */
# define KEY_E 101
# define DOOR_INTERACT_DIST 1.5
# define POKEBALL_ANIM_FRAMES 20
# define EXPLOSION_FRAMES 15
# define POKEMON_ANIM_SPEED 0.05

/* Door system functions */
void	init_doors_bonus(t_game *game);
void	draw_doors_bonus(t_game *game);
void	trigger_door_bonus(t_game *game);
void	update_doors_bonus(t_game *game);
void	free_doors_bonus(t_game *game);

/* Pokemon functions */
void	init_pokemon_bonus(t_game *game);
void	draw_pokemon_bonus(t_game *game);
void	update_pokemon_bonus(t_game *game);
void	free_pokemon_bonus(t_game *game);

/* Animation functions */
void	init_animations_bonus(t_game *game);
void	draw_pokeball_animation(t_game *game);
void	draw_explosion_animation(t_game *game);
void	update_animations_bonus(t_game *game);

/* Helper functions */
int		is_door_char(char c);
int		get_pokemon_type(char c);
t_door	*find_door_at(t_game *game, int x, int y);
int		is_player_near_door(t_game *game, t_door *door);
void	add_door_to_list(t_game *game, int x, int y);
void	remove_door_from_map(t_game *game, int x, int y);

#endif
