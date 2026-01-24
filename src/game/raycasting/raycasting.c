
#include "cub3d.h"

void compute_ray(t_game *game, int x)
{
	game->ray.camera_x = 2.0 * x / (double)LENGHT - 1;
	game->ray.dir_x = game->player.dir_x + game->player.plane_x * game->ray.camera_x;
	game->ray.dir_y = game->player.dir_y + game->player.plane_y * game->ray.camera_x;
	game->ray.map_x = (int)game->player.x;
	game->ray.map_y = (int)game->player.y;
}

void init_dda(t_game *game)
{
	if (game->ray.dir_x == 0)
		game->dda.delta_dist_x = 1e30;
	else
		game->dda.delta_dist_x = fabs(1.0 / game->ray.dir_x);
	if (game->ray.dir_y == 0)
		game->dda.delta_dist_y = 1e30;
	else
		game->dda.delta_dist_y = fabs(1.0 / game->ray.dir_y);

	if (game->ray.dir_x < 0)
	{
		game->dda.step_x = -1;
		game->dda.side_dist_x = (game->player.x - game->ray.map_x) * game->dda.delta_dist_x;
	}
	else
	{
		game->dda.step_x = 1;
		game->dda.side_dist_x = (game->ray.map_x + 1.0 - game->player.x) * game->dda.delta_dist_x;
	}

	if (game->ray.dir_y < 0)
	{
		game->dda.step_y = -1;
		game->dda.side_dist_y = (game->player.y - game->ray.map_y) * game->dda.delta_dist_y;
	}
	else
	{
		game->dda.step_y = 1;
		game->dda.side_dist_y = (game->ray.map_y + 1.0 - game->player.y) * game->dda.delta_dist_y;
	}
	game->dda.hit = 0;
}

void perform_dda(t_game *game)
{
	while (!game->dda.hit)
	{
		if (game->dda.side_dist_x < game->dda.side_dist_y)
		{
			game->dda.side_dist_x += game->dda.delta_dist_x;
			game->ray.map_x += game->dda.step_x;
			game->dda.side = 0;
		}
		else
		{
			game->dda.side_dist_y += game->dda.delta_dist_y;
			game->ray.map_y += game->dda.step_y;
			game->dda.side = 1;
		}
		if (game->ray.map_x < 0 || game->ray.map_y < 0 || 
			game->ray.map_y >= game->map.height || game->ray.map_x >= game->map.width)
		{
			game->dda.hit = 1;
		}
		else if (game->map.grid[game->ray.map_y][game->ray.map_x] == '1')
			game->dda.hit = 1;
	}
}

void compute_wall_params(t_game *game)
{
	if (game->dda.side == 0)
		game->wall.perp_dist = (game->ray.map_x - game->player.x + (1 - game->dda.step_x) / 2.0) / game->ray.dir_x;
	else
		game->wall.perp_dist = (game->ray.map_y - game->player.y + (1 - game->dda.step_y) / 2.0) / game->ray.dir_y;

	if (game->wall.perp_dist < 0.001)
		game->wall.perp_dist = 0.001;

	game->wall.line_height = (int)(HEIGHT / game->wall.perp_dist);
	if (game->wall.line_height < 1)
		game->wall.line_height = 1;
	
	game->wall.draw_start = -game->wall.line_height / 2 + HEIGHT / 2;
	if (game->wall.draw_start < 0)
		game->wall.draw_start = 0;
	game->wall.draw_end = game->wall.line_height / 2 + HEIGHT / 2;
	if (game->wall.draw_end >= HEIGHT)
		game->wall.draw_end = HEIGHT - 1;
}

void select_texture(t_game *game)
{
	if (game->dda.side == 0 && game->ray.dir_x > 0)
		game->tex.img = &game->textures.ea;
	else if (game->dda.side == 0 && game->ray.dir_x < 0)
		game->tex.img = &game->textures.we;
	else if (game->dda.side == 1 && game->ray.dir_y > 0)
		game->tex.img = &game->textures.so;
	else
		game->tex.img = &game->textures.no;
}

