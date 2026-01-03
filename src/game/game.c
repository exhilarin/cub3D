
#include "cub3d.h"

static void init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (free_game(game));
    game->win = mlx_new_window(game->mlx, LENGHT, HEIGHT, "pokemon");
    if (!game->win)
        return (free_game(game));
    game->image = mlx_new_image(game->mlx, LENGHT, HEIGHT);
    if (!game->image)
        return (free_game(game));
    game->addres = mlx_get_data_addr(game->image, &game->img_addr.bpp,
        &game->img_addr.line_lenght, &game->img_addr.endian);
    if (!game->addres)
        return (free_game(game));
}

void game_loop(t_game *game)
{
    init_mlx(game);
    init_player(game);
    key_hook(game);
    mlx_loop_hook(game->mlx, (void *)render_frame, game);
    mlx_loop(game->mlx);
}

void exit_game(t_game *game)
{
    free_game(game);
    exit(0);
}