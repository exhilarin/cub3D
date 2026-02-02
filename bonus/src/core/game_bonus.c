/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/02 22:25:59 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	load_textures_bonus(t_game *game)
{
	load_texture(game, &game->textures.no, game->textures.north);
	load_texture(game, &game->textures.so, game->textures.south);
	load_texture(game, &game->textures.we, game->textures.west);
	load_texture(game, &game->textures.ea, game->textures.east);
	load_texture(game, &game->textures.grass, "./assets/floor.xpm");
}

void	init_mlx_bonus(t_game *game)
{
	init_mlx_display(game);
	init_mlx_image(game);
	load_textures_bonus(game);
}

static void	exit_game_bonus(t_game *game)
{
	mlx_loop_end(game->mlx);
	free_bonus_resources(game);
	free_game(game);
	exit(0);
}

static int	close_window_bonus(t_game *game)
{
	mlx_loop_end(game->mlx);
	free_bonus_resources(game);
	free_game(game);
	exit(0);
	return (0);
}

static void	key_hook_bonus(t_game *game);

void	game_loop_bonus(t_game *game)
{
	init_mlx_bonus(game);
	game->intro_active = 1;
	load_intro_screen_bonus(game);
	init_player(game);
	init_minimap(game, &game->minimap);
	init_doors_bonus(game);
	init_pokemon_bonus(game);
	init_animations_bonus(game);
	init_mouse_bonus(game);
	key_hook_bonus(game);
	mlx_hook(game->win, 17, 0, close_window_bonus, game);
	mlx_loop_hook(game->mlx, (void *)render_frame_bonus, game);
	mlx_loop(game->mlx);
}

static int	mouse_click_bonus(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)  /* Left mouse button */
	{
		trigger_hand_animation(game);
		trigger_door_bonus(game);
	}
	return (0);
}

static int	key_press_bonus(int keycode, t_game *game)
{
	if (keycode == KEY_SPACE && game->intro_active)
	{
		start_game_bonus(game);
		return (0);
	}
	if (keycode == KEY_W)
		game->player.move_forward = 1;
	else if (keycode == KEY_S)
		game->player.move_backward = 1;
	else if (keycode == KEY_A)
		game->player.move_left = 1;
	else if (keycode == KEY_D)
		game->player.move_right = 1;
	else if (keycode == KEY_LEFT)
		game->player.rotate_left = 1;
	else if (keycode == KEY_RIGHT)
		game->player.rotate_right = 1;
	else if (keycode == KEY_SHIFT)
		game->player.shift_pressed = 1;
	else if (keycode == KEY_ESC)
		exit_game_bonus(game);
	else if (keycode == KEY_E)
	{
		trigger_hand_animation(game);
		trigger_door_bonus(game);
	}
	return (0);
}

static int	key_release_bonus(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.move_forward = 0;
	else if (keycode == KEY_S)
		game->player.move_backward = 0;
	else if (keycode == KEY_A)
		game->player.move_left = 0;
	else if (keycode == KEY_D)
		game->player.move_right = 0;
	else if (keycode == KEY_LEFT)
		game->player.rotate_left = 0;
	else if (keycode == KEY_RIGHT)
		game->player.rotate_right = 0;
	else if (keycode == KEY_SHIFT)
		game->player.shift_pressed = 0;
	return (0);
}

static void	key_hook_bonus(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press_bonus, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_bonus, game);
	mlx_hook(game->win, 6, 1L << 6, handle_mouse_move_bonus, game);
	mlx_mouse_hook(game->win, mouse_click_bonus, game);
}
