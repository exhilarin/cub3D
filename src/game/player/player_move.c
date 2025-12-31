
#include "cub3d.h"

static void rotate_left(t_game *game)
{
    double old_dir_x;
    double old_plane_x;
    double rotation_speed;

    old_dir_x = game->player.dir_x;
    old_plane_x = game->player.plane_x;
    rotation_speed = game->player.rotate_speed;
    game->player.dir_x = game->player.dir_x * cos(rotation_speed)
        - game->player.dir_y * sin(rotation_speed);
    game->player.dir_y = old_dir_x * sin(rotation_speed)
        + game->player.dir_y * cos(rotation_speed);
    game->player.plane_x = game->player.plane_x * cos(rotation_speed)
        - game->player.plane_y * sin(rotation_speed);
    game->player.plane_y = old_plane_x * sin(rotation_speed)
        + game->player.plane_y * cos(rotation_speed);
}

static void rotate_right(t_game *game)
{
    double old_dir_x;
    double old_plane_x;
    double rotation_speed;

    old_dir_x = game->player.dir_x;
    old_plane_x = game->player.plane_x;
    rotation_speed = -game->player.rotate_speed;
    game->player.dir_x = game->player.dir_x * cos(rotation_speed)
        - game->player.dir_y * sin(rotation_speed);
    game->player.dir_y = old_dir_x * sin(rotation_speed)
        + game->player.dir_y * cos(rotation_speed);
    game->player.plane_x = game->player.plane_x * cos(rotation_speed)
        - game->player.plane_y * sin(rotation_speed);
    game->player.plane_y = old_plane_x * sin(rotation_speed)
        + game->player.plane_y * cos(rotation_speed);
}

static void rotate_player(t_game *game)
{
    if (game->player.rotate_left)
        rotate_left(game);
    if (game->player.rotate_right)
        rotate_right(game);
}

static void move_player(t_game *game)
{
    if (game->player.move_forward)
    {
        game->player.x += game->player.dir_x * game->player.move_speed;
        game->player.y += game->player.dir_y * game->player.move_speed;
    }
    if (game->player.move_backward)
    {
        game->player.x -= game->player.dir_x * game->player.move_speed;
        game->player.y -= game->player.dir_y * game->player.move_speed;
    }
    if (game->player.move_left)
    {
        game->player.x -= game->player.plane_x * game->player.move_speed;
        game->player.y -= game->player.plane_y * game->player.move_speed;
    }
    if (game->player.move_right)
    {
        game->player.x += game->player.plane_x * game->player.move_speed;
        game->player.y += game->player.plane_y * game->player.move_speed;
    }
}

void update_player(t_game *game)
{
    move_player(game);
    rotate_player(game);
}