/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 21:07:56 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/12/30 22:18:31 by ilyas-guney      ###   ########.fr       */
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
# include "structs.h"
# include "config.h"

/* --- Parsing Functions --- */
void	parse_file(char *file, t_game *game);
void	parse_textures(char *line, t_game *game);
void	parse_colors(char *line, t_game *game);
int		parse_map(char *first_line, int fd, t_game *game);
void	validate_map(t_game *game);

/* --- Utils Functions --- */
void	ft_perror(const char *str);
void	init_data(t_game *game);
int		is_valid_map_char(char c);
int		skip_whitespace(char *str);

/* --- Free Functions --- */
void	free_split(char **tab);
void	free_game(t_game *game);
void    free_mlx(t_game *game);

/* --- Game Functions --- */
void game_loop(t_game *game);
void player_init(t_game *game);
void key_hook(t_game *game);
void exit_game(t_game *game);

#endif