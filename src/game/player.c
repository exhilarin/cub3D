
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

void player_init(t_game *game)
{
    game->player.x = game->map.player_x + 0.5;
    game->player.y = game->map.player_y + 0.5;
    set_dir(game);
    set_plane(game);
}