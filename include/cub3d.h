/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 21:07:56 by ilyas-guney       #+#    #+#             */
/*   Updated: 2026/01/27 06:22:38 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../library/libft/libft.h"
# include "../library/gnl/get_next_line.h"
# include "../library/minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "structs.h"
# include "config.h"

/* --- Parsing Functions --- */
void	parse_file(char *file, t_game *game);
void	parse_textures(char *line, t_game *game);
void	parse_colors(char *line, t_game *game);
int		parse_map(char *first_line, int fd, t_game *game);
void	validate_map(t_game *game);
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
int		check_wall(t_game *game, int x, int y);
void	move(t_game *game);

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

#endif