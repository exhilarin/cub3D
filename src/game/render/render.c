
#include "cub3d.h"

static void draw_floor_ceiling(t_game *game)
{
    unsigned int color;
    char *pixel_addr;
    int x;
    int y;

    y = 0;
    while (y < HEIGHT)
    {
        if (y < HEIGHT / 2)
            color = game->textures.ceiling_color;
        else
            color = game->textures.floor_color;
        x = 0;
        while (x < LENGHT)
        {
            pixel_addr = game->img_addr.addr + (y * game->img_addr.line_lenght
                    + x * (game->img_addr.bpp / 8));
            *(unsigned int *)pixel_addr = color;
            x++;
        }
        y++;
    }
}


// TODO: Collision detection and wall rendering

void	draw_walls(t_game *game)
{
	int	x;

	x = 0;
	while (x < LENGHT)
	{
		compute_ray(game, x);
		init_dda(game);
		perform_dda(game);
		compute_wall_params(game);
		select_texture(game);
		compute_texcoords(game);
		draw_vertical_stripe(game, x);
		x++;
	}
}

void render_frame(t_game *game)
{
    update_player(game);
    draw_floor_ceiling(game);
    draw_walls(game);
    // draw_sprites(game);
    mlx_put_image_to_window(game->mlx, game->win, game->image, 0, 0);
}