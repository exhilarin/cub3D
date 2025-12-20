/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 21:07:56 by ilyas-guney       #+#    #+#             */
/*   Updated: 2025/10/28 21:07:57 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../library/libft/libft.h"
# include "../library/gnl/get_next_line.h"
//# include "../library/minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_texture
{
    char    *north;
    char    *south;
    char    *west;
    char    *east;
    int     floor_color;
    int     ceiling_color;
    int     c_count;
}               t_texture;

typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    int     player_count;
    char    player_dir;
    double  player_x;
    double  player_y;
}               t_map;

typedef struct s_game
{
    t_texture   textures;
    t_map       map;
    void        *mlx;
    void        *win;
    int         map_fd;
    char        *map_path;
}               t_game;

/* --- Parsing Functions --- */
void    parse_file(char *file, t_game *game);
void    parse_textures(char *line, t_game *game);
void    parse_colors(char *line, t_game *game);
int     parse_map(char *first_line, int fd, t_game *game);
void    validate_map(t_game *game);

/* --- Utils Functions --- */
void    ft_perror(const char *str);
void    init_data(t_game *game);
char    *gnl_strjoin(char *s1, char *s2);
int     is_valid_map_char(char c);
int     skip_whitespace(char *str);

/* --- Free Functions --- */
void    free_split(char **tab);
void    free_game(t_game *game);

#endif