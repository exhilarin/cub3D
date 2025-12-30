
#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor_color;
	int		ceiling_color;
	int		c_count;
}			t_texture;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_count;
	char	player_dir;
	double	player_x;
	double	player_y;
}			t_map;

typedef struct s_addr
{
	char	*addr;
	int		bpp;
	int		line_lenght;
	int		endian;
} 				t_addr;

typedef struct s_game
{
	t_texture	textures;
	t_addr		img_addr;
	t_map		map;
	void		*mlx;
	void		*win;
	void		*image;
	int			map_fd;
	char		*map_path;
	char		*addres;
}				t_game;


#endif