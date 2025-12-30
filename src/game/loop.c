
#include "cub3d.h"

static void init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (free_game(game));
    game->win = mlx_new_window(game->mlx, LENGHT, HEIGHT, "pokemon");
    if (!game->win)
        return (free_game(game), free(game->win));
    game->image = mlx_new_image(game->mlx, LENGHT, HEIGHT);
    if (!game->image)
        return (free_game(game), free(game->win), free(game->mlx));
    game->addres = mlx_get_data_addr(game->image, &game->img_addr.bpp,
        &game->img_addr.line_lenght, &game->img_addr.endian);
    if (!game->addres)
        return (free_game(game), free(game->win), free(game->mlx));
}

static void render_frame(t_game *game)
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
    mlx_put_image_to_window(game->mlx, game->win, game->image, 0, 0);
}

// Player Initialization
// Input Hook setup

void exit_game(t_game *game)
{
    free_game(game);
    exit(0);
}

void game_loop(t_game *game)
{
    init_mlx(game);
    player_init(game);
    key_hook(game);
    mlx_loop_hook(game->mlx, (void *)render_frame, game);
    mlx_loop(game->mlx);
}
