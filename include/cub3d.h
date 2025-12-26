/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 21:07:56 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/12/26 22:38:16 by iguney           ###   ########.fr       */
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

#define LENGHT 1920
#define HEIGHT 1080

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

/* --- Game Functions --- */
void game_loop(t_game *game);



#endif