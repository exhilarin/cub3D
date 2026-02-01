/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 21:07:56 by ilyas-guney       #+#    #+#             */
/*   Updated: 2026/02/01 06:30:00 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../../library/libft/libft.h"
# include "../../library/gnl/get_next_line.h"
# include "../../library/minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "structs_bonus.h"
# include "config_bonus.h"

/* Forward declarations for bonus features */
# include "../src/ui/minimap_bonus.h"
# include "../src/entities/door_bonus.h"

/* --- Parsing Functions --- */
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

/* --- Utils Functions --- */
void	ft_perror(const char *str);
void	init_data(t_game *game);
int		is_valid_map_char(char c);
int		skip_whitespace(char *str);

/* --- Free Functions --- */
void	free_split(char **tab);
void	free_game(t_game *game);
void	free_mlx(t_game *game);

/* --- Game Functions --- */
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
void	update_player_speed(t_game *game);

/* --- Raycasting Functions --- */
void	draw_walls(t_game *game);
void	compute_ray(t_game *game, int x);
void	init_dda(t_game *game);
void	perform_dda(t_game *game);
void	compute_wall_params(t_game *game);
void	select_texture(t_game *game);
void	compute_texcoords(t_game *game);
void	draw_vertical_stripe(t_game *game, int x);
void	draw_pixel(t_game *game, int x, int y, int tex_y);

/* --- BONUS-SPECIFIC FUNCTIONS --- */

/* Mouse Rotation Bonus */
int		handle_mouse_move_bonus(int x, int y, t_game *game);
void	init_mouse_bonus(t_game *game);

/* Wall Collision Bonus */
int		check_wall_bonus(t_game *game, int x, int y);
int		collision_detection_bonus(t_game *game);
void	move_bonus(t_game *game);

/* Player Movement Bonus (with collision) */
void	update_player_bonus(t_game *game);
void	update_player_speed_bonus(t_game *game);

/* Game Loop Bonus */
void	game_loop_bonus(t_game *game);
void	render_frame_bonus(t_game *game);

/* Minimap Bonus */
typedef struct s_minimap	t_minimap;
void	init_minimap(t_game *game, t_minimap *minimap);
void	draw_minimap(t_game *game, t_minimap *minimap);
void	draw_minimap_with_border(t_game *game, t_minimap *minimap);

/* Door + Pokemon Bonus */
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

/* Floor/Ceiling Drawing Bonus */
void	draw_floor_ceiling_bonus(t_game *game);

#endif