
#include "cub3d.h"

static void draw_floor_ceiling(t_game *game)
{
    unsigned int    color;
    char            *pixel_adrr;
    for (int y = 0; y < HEIGHT; y++)
    {
        if (y < HEIGHT / 2)
            color = game->textures.ceiling_color;
        else
            color = game->textures.floor_color;
        for (int x = 0; x < LENGHT; x++)
        {
            pixel_adrr = game->addres + (y * game->img_addr.line_lenght + x 
                * (game->img_addr.bpp / 8));
            *(unsigned int *)pixel_adrr = color;
        }
    }
}

// TODO: Collision detection and wall rendering

void render_frame(t_game *game)
{
    update_player(game);
    draw_floor_ceiling(game);
    // draw_walls(game);
    // draw_sprites(game);
    mlx_put_image_to_window(game->mlx, game->win, game->image, 0, 0);
}