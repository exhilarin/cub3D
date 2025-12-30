
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
    game->addres = mlx_get_data_addr(game->image, &game->img_addr.bpp, &game->img_addr.line_lenght, &game->img_addr.endian);
    if (!game->addres)
        return (free_game(game), free(game->win), free(game->mlx));
}

static void render_frame(t_game *game)
{
    char *pixel_adrr;
    char *color;
    for (int y = 0; y < HEIGHT; y++)
    {
        if (y < HEIGHT / 2)
            color = game->textures.floor_color;
        else
            color = game->textures.ceiling_color;
        for (int x = 0; x < LENGHT; x++)
            pixel_adrr = game->addres + (y * game->img_addr.line_lenght + x 
                    * (game->img_addr.bpp / 8));
    }
    mlx_put_image_to_window(game->mlx, game->win, game->image, 0, 0);
}

static void free_mlx(t_game *game)
{
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->image)
        mlx_destroy_image(game->mlx, game->image);
}

void game_loop(t_game *game)
{
    init_mlx(game);
    mlx_loop_hook(game->mlx, render_frame, game);
    mlx_loop(game->mlx);
}
