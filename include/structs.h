
#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_lenght;
    int     endian;
}               t_img;

typedef struct s_texture
{
    char    *north;
    char    *south;
    char    *west;
    char    *east;
    int     floor_color;
    int     ceiling_color;
    int     c_count;

    t_img   no;
    t_img   so;
    t_img   we;
    t_img   ea;
}               t_texture;


typedef struct s_texinfo
{
    t_img  *img;
    int    tex_x;
    double step;
    double tex_pos;
}   t_texinfo;

typedef struct s_ray
{
    double camera_x;
    double dir_x;
    double dir_y;
    int    map_x;
    int    map_y;
}   t_ray;

typedef struct s_dda
{
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    int    step_x;
    int    step_y;
    int    hit;
    int    side;
}   t_dda;

typedef struct s_wall
{
    double perp_dist;
    int    line_height;
    int    draw_start;
    int    draw_end;
}   t_wall;

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

typedef struct s_addr
{
    char    *addr;
    int     bpp;
    int     line_lenght;
    int     endian;
}               t_addr;

typedef struct s_player
{
    double  x;
    double  y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;

    double  new_x;
    double  new_y;

    double  move_speed;
    double  rotate_speed;

    int     move_forward;
    int     move_backward;
    int     move_left;
    int     move_right;
    int     rotate_left;
    int     rotate_right;
}               t_player;

typedef struct s_game
{
    t_texture   textures;
    t_addr      img_addr;
    t_map       map;
    t_player    player;

    t_ray       ray;
    t_dda       dda;
    t_wall      wall;
    t_texinfo   tex;

    void        *mlx;
    void        *win;
    void        *image;

    int         map_fd;
    char        *map_path;
    char        *addres;
}   t_game;


#endif