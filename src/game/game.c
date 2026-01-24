
#include "cub3d.h"

static void load_texture(t_game *game, t_img *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(game->mlx, path, 
        &texture->width, &texture->height);
    if (!texture->img)
    {
        ft_perror("Error\nFailed to load texture\n");
    }
    texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
        &texture->line_lenght, &texture->endian);
    if (!texture->addr)
    {
        ft_perror("Error\nFailed to get texture data\n");
    }
}

static void load_textures(t_game *game)
{
    load_texture(game, &game->textures.no, game->textures.north);
    load_texture(game, &game->textures.so, game->textures.south);
    load_texture(game, &game->textures.we, game->textures.west);
    load_texture(game, &game->textures.ea, game->textures.east);
}

static void init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        ft_perror("Error\nFailed to initialize MLX\n");
    game->win = mlx_new_window(game->mlx, LENGHT, HEIGHT, "cub3D");
    if (!game->win)
        ft_perror("Error\nFailed to create window\n");
    game->image = mlx_new_image(game->mlx, LENGHT, HEIGHT);
    if (!game->image)
        ft_perror("Error\nFailed to create image\n");
    game->img_addr.addr = mlx_get_data_addr(game->image, &game->img_addr.bpp,
        &game->img_addr.line_lenght, &game->img_addr.endian);
    if (!game->img_addr.addr)
        ft_perror("Error\nFailed to get image data\n");
    load_textures(game);
}

static int close_window(t_game *game)
{
    mlx_loop_end(game->mlx);
    free_game(game);
    exit(0);
    return (0);
}

void game_loop(t_game *game)
{
    init_mlx(game);
    init_player(game);
    key_hook(game);
    mlx_hook(game->win, 17, 0, close_window, game);
    mlx_loop_hook(game->mlx, (void *)render_frame, game);
    mlx_loop(game->mlx);
}

void exit_game(t_game *game)
{
    mlx_loop_end(game->mlx);
    free_game(game);
    exit(0);
}