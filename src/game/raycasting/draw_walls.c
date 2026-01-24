
#include "cub3d.h"

void compute_texcoords(t_game *game)
{
	double wall_x;

	if (game->dda.side == 0)
		wall_x = game->player.y + game->wall.perp_dist * game->ray.dir_y;
	else
		wall_x = game->player.x + game->wall.perp_dist * game->ray.dir_x;
	wall_x -= floor(wall_x);

	game->tex.tex_x = (int)(wall_x * (double)game->tex.img->width);
	if (game->tex.tex_x >= game->tex.img->width)
		game->tex.tex_x = game->tex.img->width - 1;
	if (game->tex.tex_x < 0)
		game->tex.tex_x = 0;

	game->tex.step = 1.0 * game->tex.img->height / game->wall.line_height;
	game->tex.tex_pos = (game->wall.draw_start - HEIGHT / 2 + game->wall.line_height / 2) * game->tex.step;
}

void draw_vertical_stripe(t_game *game, int x)
{
	int y;
	int tex_y;
	unsigned int color;
	char *dst;

	if (!game->tex.img || !game->tex.img->addr)
		return;

	y = game->wall.draw_start;
	while (y <= game->wall.draw_end)
	{
		if (y >= 0 && y < HEIGHT && x >= 0 && x < LENGHT)
		{
			tex_y = (int)game->tex.tex_pos & (game->tex.img->height - 1);
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= game->tex.img->height)
				tex_y = game->tex.img->height - 1;
			
			game->tex.tex_pos += game->tex.step;
			dst = game->img_addr.addr + (y * game->img_addr.line_lenght + x * (game->img_addr.bpp / 8));
			color = *(unsigned int *)(game->tex.img->addr + (tex_y * game->tex.img->line_lenght
					+ game->tex.tex_x * (game->tex.img->bpp / 8)));
			*(unsigned int *)dst = color;
		}
		y++;
	}
}

