/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 21:07:56 by ilyas-guney       #+#    #+#             */
/*   Updated: 2026/02/01 10:00:00 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

/* ==================== SYSTEM INCLUDES ==================== */
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>

/* ==================== PROJECT LIBRARIES ==================== */
# include "../../library/libft/libft.h"
# include "../../library/gnl/get_next_line.h"
# include "../../library/minilibx-linux/mlx.h"

/* ==================== BONUS CONFIGURATION ==================== */
# include "config_bonus.h"
# include "structs_bonus.h"

/* ==================== MINIMAP CONFIGURATION ==================== */
# define MINIMAP_SIZE 200
# define MINIMAP_MARGIN 20
# define MINIMAP_BG_COLOR 0x90EE90
# define MINIMAP_FLOOR_COLOR 0x90EE90
# define MINIMAP_WALL_COLOR 0x228B50
# define MINIMAP_PLAYER_COLOR 0xFF3050
# define MINIMAP_DIRECTION_COLOR 0xFF3050
# define MINIMAP_PLAYER_SIZE 5
# define MINIMAP_BORDER_COLOR 0xFF5050

/* Pokemon Colors for Minimap */
# define MINIMAP_PIKACHU_COLOR 0xFFD450
# define MINIMAP_SNORLAX_COLOR 0x4169E1
# define MINIMAP_CHARIZARD_COLOR 0xFF8C00
# define MINIMAP_POKEMON_SIZE 4
# define MINIMAP_POKEMON_SIZE 4

/* ==================== DOOR & POKEMON CONFIGURATION ==================== */
# define SPRITE_POKEBALL "./assets/sprites/effects/pokeball.xpm"
# define SPRITE_EXPLOSION "./assets/sprites/effects/explosion.xpm"
# define SPRITE_PIKACHU "./assets/sprites/pokemon/pikachu/"
# define SPRITE_SNORLAX "./assets/sprites/pokemon/snorlax/"
# define SPRITE_CHARIZARD "./assets/sprites/pokemon/charizard/"

# define DOOR_PIKACHU 'P'
# define DOOR_SNORLAX 'X'
# define DOOR_CHARIZARD 'C'

# define POKEMON_PIKACHU 0
# define POKEMON_SNORLAX 1
# define POKEMON_CHARIZARD 2

# define PIKACHU_FRAMES 32
# define SNORLAX_FRAMES 90
# define CHARIZARD_FRAMES 19

# define KEY_E 101
# define DOOR_INTERACT_DIST 1.5
# define POKEBALL_ANIM_FRAMES 35
# define POKEBALL_FRAMES 7
# define EXPLOSION_FRAMES 15
# define FADE_SPEED 8
# define MAX_ALPHA 255
# define FADE_SPEED 8
# define MAX_ALPHA 255
# define POKEMON_ANIM_SPEED 0.05

/* ==================== PARSING FUNCTIONS ==================== */
void	parse_file(char *file, t_game *game);
void	parse_textures(char *line, t_game *game);
void	parse_colors(char *line, t_game *game);
int		parse_map(char *first_line, int fd, t_game *game);
void	validate_map(t_game *game);
void	validate_map_connectivity(t_game *game);
int		is_map_line(char *line);
int		is_texture_id(char *s);
int		is_color_id(char *s);
void	check_all_elements(t_game *game);
int		split_len(char **tab);
int		check_isdigit(char *str);
int		calculate_rgb(char **rgb);
void	check_adjacent_commas(char *line, char **rgb, t_game *game);
int		count_commas(char *line);

/* ==================== UTILS FUNCTIONS ==================== */
void	ft_perror(const char *str);
void	init_data(t_game *game);
int		is_valid_map_char(char c);
int		skip_whitespace(char *str);

/* ==================== FREE FUNCTIONS ==================== */
void	free_split(char **tab);
void	free_game(t_game *game);
void	free_mlx(t_game *game);

/* ==================== GAME FUNCTIONS ==================== */
void	game_loop(t_game *game);
void	init_player(t_game *game);
void	key_hook(t_game *game);
void	render_frame(t_game *game);
void	update_player(t_game *game);
void	exit_game(t_game *game);
void	init_mlx(t_game *game);
void	init_mlx_display(t_game *game);
void	init_mlx_image(t_game *game);
void	load_texture(t_game *game, t_img *texture, char *path);
void	load_textures(t_game *game);

/* ==================== RAYCASTING FUNCTIONS ==================== */
void	draw_walls(t_game *game);
void	compute_ray(t_game *game, int x);
void	init_dda(t_game *game);
void	perform_dda(t_game *game);
void	compute_wall_params(t_game *game);
void	select_texture(t_game *game);
void	compute_texcoords(t_game *game);
void	draw_vertical_stripe(t_game *game, int x);
void	draw_pixel(t_game *game, int x, int y, int tex_y);

/* ==================== BONUS CORE FUNCTIONS ==================== */
void	game_loop_bonus(t_game *game);
void	render_frame_bonus(t_game *game);
void	draw_floor_ceiling_bonus(t_game *game);
void	init_mlx_bonus(t_game *game);
void	load_textures_bonus(t_game *game);
void	free_bonus_resources(t_game *game);
void	draw_transparent_image(t_game *game, t_img *img, int x, int y);
void	draw_scaled_transparent_image(t_game *game, t_img *img, int x, int y,
			float scale);

/* ==================== MINIMAP FUNCTIONS ==================== */
void	init_minimap(t_game *game, t_minimap *minimap);
void	draw_minimap(t_game *game, t_minimap *minimap);
void	draw_minimap_with_border(t_game *game, t_minimap *minimap);

/* Minimap Drawing Functions */
void	put_pixel_minimap(t_game *game, int x, int y, int color);
int		is_outer_wall(t_game *game, int mx, int my);
void	draw_minimap_tile(t_game *game, t_minimap *mm, int mx, int my);

/* Minimap Player Functions */
void	draw_player_square(t_game *game, t_minimap *mm);
void	draw_player_direction(t_game *game, t_minimap *mm);
void	draw_player_on_minimap(t_game *game, t_minimap *mm);

/* Minimap Pokemon Functions */
void	draw_pokemon_on_minimap(t_game *game, t_minimap *minimap);

/* ==================== MOUSE FUNCTIONS ==================== */
int		handle_mouse_move_bonus(int x, int y, t_game *game);
void	init_mouse_bonus(t_game *game);

/* ==================== COLLISION FUNCTIONS ==================== */
int		check_wall_bonus(t_game *game, int x, int y);
int		check_solid_pokemon(t_game *game, int x, int y);
int		collision_detection_bonus(t_game *game);
void	move_bonus(t_game *game);
void	update_player_bonus(t_game *game);
void	update_player_speed_bonus(t_game *game);

/* ==================== DOOR FUNCTIONS ==================== */
void	init_doors_bonus(t_game *game);
void	update_doors_bonus(t_game *game);
void	draw_doors_bonus(t_game *game);
void	trigger_door_bonus(t_game *game);
void	free_doors_bonus(t_game *game);
void	add_door_to_list(t_game *game, int x, int y);
void	remove_door_from_map(t_game *game, int x, int y);
int		is_door_char(char c);
int		get_pokemon_type(char c);
t_door	*find_closest_door_bonus(t_game *game);
int		is_player_near_door(t_game *game, t_door *door);

/* ==================== SPRITE FUNCTIONS ==================== */
void	init_pokemon_bonus(t_game *game);
void	update_pokemon_bonus(t_game *game);
void	draw_pokemon_bonus(t_game *game);
void	free_pokemon_bonus(t_game *game);

/* Pokemon Loading Functions */
void	load_pikachu_frames(t_game *game, t_pokemon *poke);
void	load_snorlax_frames(t_game *game, t_pokemon *poke);
void	load_charizard_frames(t_game *game, t_pokemon *poke);

/* Animation Functions */
void	update_animations_bonus(t_game *game);
void	init_animations_bonus(t_game *game);
void	draw_explosion_animation(t_game *game);
void	draw_pokeball_animation(t_game *game);

#endif