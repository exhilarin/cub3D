
#include "cub3d.h"

static void set_dir(t_game *game)
{
    if (game->map.player_dir == 'N')
    {
        game->player.dir_x = 0;
        game->player.dir_y = -1;
    }
    else if (game->map.player_dir == 'S')
    {
        game->player.dir_x = 0;
        game->player.dir_y = 1;
    }
    else if (game->map.player_dir == 'E')
    {
        game->player.dir_x = 1;
        game->player.dir_y = 0;
    }
    else if (game->map.player_dir == 'W')
    {
        game->player.dir_x = -1;
        game->player.dir_y = 0;
    }
}

static void set_plane(t_game *game)
{
    if (game->map.player_dir == 'N')
    {
        game->player.plane_x = 0;
        game->player.plane_y = FOV;
    }
    else if (game->map.player_dir == 'S')
    {
        game->player.plane_x = 0;
        game->player.plane_y = -FOV;
    }
    else if (game->map.player_dir == 'E')
    {
        game->player.plane_x = FOV;
        game->player.plane_y = 0;
    }
    else if (game->map.player_dir == 'W')
    {
        game->player.plane_x = -FOV;
        game->player.plane_y = 0;
    }
}

void init_player(t_game *game)
{
    game->player.move_speed = 0.05;
    game->player.rotate_speed = 0.03;
    game->player.move_forward = 0;
    game->player.move_backward = 0;
    game->player.move_left = 0;
    game->player.move_right = 0;
    game->player.rotate_left = 0;
    game->player.rotate_right = 0;
    game->player.x = game->map.player_x + 0.5;
    game->player.y = game->map.player_y + 0.5;
    set_dir(game);
    set_plane(game);
}
