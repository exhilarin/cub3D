/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 02:21:09 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_lenght;
	int		endian;
}	t_img;

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor_color;
	int		ceiling_color;
	int		c_count;
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
}	t_texture;

typedef struct s_texinfo
{
	t_img	*img;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_texinfo;

typedef struct s_dda
{
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_dda;

typedef struct s_wall
{
	double	perp_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_wall;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_count;
	char	player_dir;
	double	player_x;
	double	player_y;
}	t_map;

typedef struct s_addr
{
	char	*addr;
	int		bpp;
	int		line_lenght;
	int		endian;
}	t_addr;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	new_x;
	double	new_y;
	double	move_speed;
	double	rotate_speed;
	double	current_speed;
	double	target_speed;
	int		move_forward;
	int		move_backward;
	int		move_left;
	int		move_right;
	int		rotate_left;
	int		rotate_right;
	int		shift_pressed;
	int		last_mouse_x;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
}	t_ray;

typedef struct s_minimap
{
	int		size;
	int		offset_x;
	int		offset_y;
	int		tile_size;
	int		player_x;
	int		player_y;
}	t_minimap;

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN
}	t_door_state;

typedef enum e_anim_type
{
	ANIM_NONE,
	ANIM_POKEBALL,
	ANIM_EXPLOSION
}	t_anim_type;

typedef struct s_door
{
	int				map_x;
	int				map_y;
	t_door_state	state;
	void			*sprite;
	struct s_door	*next;
}	t_door;

typedef struct s_pokemon
{
	int					map_x;
	int					map_y;
	void				*sprite;
	int					anim_offset;
	int					active;
	struct s_pokemon	*next;
}	t_pokemon;

typedef struct s_anim
{
	t_anim_type	type;
	int			frame_count;
	int			map_x;
	int			map_y;
	void		*pokeball_img;
	void		*explosion_img;
}	t_anim;

typedef struct s_game
{
	t_texture	textures;
	t_addr		img_addr;
	t_map		map;
	t_player	player;
	t_ray		ray;
	t_dda		dda;
	t_wall		wall;
	t_texinfo	tex;
	t_minimap	minimap;
	t_door		*doors;
	t_pokemon	*pokemons;
	t_anim		anim;
	void		*mlx;
	void		*win;
	void		*image;
	int			map_fd;
	char		*map_path;
	char		*addres;
}	t_game;

#endif