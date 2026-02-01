/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 09:11:12 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "include/structs_bonus.h"
# include "include/config_bonus.h"
# include "src/ui/minimap_bonus.h"
# include "src/entities/door_bonus.h"

/* --- Mouse Rotation Bonus --- */
int		handle_mouse_move_bonus(int x, int y, t_game *game);
void	init_mouse_bonus(t_game *game);

/* --- Wall Collision Bonus --- */
int		check_wall_bonus(t_game *game, int x, int y);
int		check_solid_pokemon(t_game *game, int x, int y);
int		collision_detection_bonus(t_game *game);
void	move_bonus(t_game *game);

/* --- Player Movement Bonus (with collision) --- */
void	update_player_bonus(t_game *game);
void	update_player_speed_bonus(t_game *game);

/* --- Game Loop Bonus --- */
void	game_loop_bonus(t_game *game);
void	render_frame_bonus(t_game *game);

/* --- Minimap Bonus --- */
typedef struct s_minimap	t_minimap;
void	init_minimap(t_game *game, t_minimap *minimap);
void	draw_minimap(t_game *game, t_minimap *minimap);
void	draw_minimap_with_border(t_game *game, t_minimap *minimap);

/* --- Door + Pokemon Bonus --- */
void	init_doors_bonus(t_game *game);
void	draw_doors_bonus(t_game *game);
void	trigger_door_bonus(t_game *game);
void	update_doors_bonus(t_game *game);
void	free_doors_bonus(t_game *game);
void	init_pokemon_bonus(t_game *game);
void	draw_pokemon_bonus(t_game *game);
void	update_pokemon_bonus(t_game *game);
void	free_pokemon_bonus(t_game *game);
void	init_animations_bonus(t_game *game);
void	draw_pokeball_animation(t_game *game);
void	draw_explosion_animation(t_game *game);
void	update_animations_bonus(t_game *game);
void	free_bonus_resources(t_game *game);
void	draw_transparent_image(t_game *game, t_img *img, int x, int y);
void	load_textures_bonus(t_game *game);
void	init_mlx_bonus(t_game *game);

#endif
