/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_anim_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/02 16:53:59 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include <sys/time.h>

static double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	load_hand_frames(t_game *game)
{
	char	path[100];
	int		i;

	i = 0;
	while (i < HAND_FRAMES)
	{
		snprintf(path, sizeof(path),
			"./assets/sprites/pokeball/frame_%d_delay-0.2s.xpm", i);
		game->hand_frames[i].img = mlx_xpm_file_to_image(game->mlx,
				path, &game->hand_frames[i].width,
				&game->hand_frames[i].height);
		if (game->hand_frames[i].img)
			game->hand_frames[i].addr = mlx_get_data_addr(
					game->hand_frames[i].img, &game->hand_frames[i].bpp,
					&game->hand_frames[i].line_lenght,
					&game->hand_frames[i].endian);
		i++;
	}
}

void	trigger_hand_animation(t_game *game)
{
	game->hand_animating = 1;
	game->hand_current_frame = 0;
	game->hand_last_time = get_time();
}

void	update_hand_animation(t_game *game)
{
	double	current_time;

	if (!game->hand_animating)
		return ;
	current_time = get_time();
	if (current_time - game->hand_last_time >= HAND_FRAME_DELAY)
	{
		game->hand_current_frame++;
		if (game->hand_current_frame >= HAND_FRAMES)
		{
			game->hand_animating = 0;
			game->hand_current_frame = 0;
		}
		game->hand_last_time = current_time;
	}
}

void	draw_hand_hud(t_game *game)
{
	t_img	*frame;
	int		x;
	int		y;

	if (!game->hand_animating)
		frame = &game->hand_frames[0];
	else
		frame = &game->hand_frames[game->hand_current_frame];
	if (!frame || !frame->img)
		return ;
	x = LENGHT - (int)(frame->width * 1.1) - 30;
	y = HEIGHT - (int)(frame->height * 1.1);
	draw_scaled_transparent_image(game, frame, x, y, 1.1);
}
