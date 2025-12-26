
#include "cub3d.h"

void game_loop(t_game *game)
{

    game->mlx = mlx_init();
    if (!game->mlx)
        return (free_game(game));
    game->win = mlx_new_window(game->mlx, LENGHT, HEIGHT, "pokemon");
    if (!game->win)
        return (free_game(game), free(game->win));
    void *image = mlx_new_image(game->mlx, LENGHT, HEIGHT);
    if (!image)
        return (free_game(game), free(game->win), free(game->mlx));
    game->addres = mlx_get_data_addr(image, &game->addr.bpp, &game->addr.line_lenght, &game->addr.endian);
    if (!game->addres)
        return (free_game(game), free(game->win), free(game->mlx));
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < LENGHT; x++)
        {
            char *pixel_adress = game->addres + (y * game->addr.line_lenght + x * (game->addr.bpp / 8));
            *(unsigned int *)pixel_adress = 0x000000FF;
        }
    }
    mlx_put_image_to_window(game->mlx, game->win, image, 0, 0);
    mlx_loop(game->mlx);
}
