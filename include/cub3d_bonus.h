/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 00:54:35 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"

/* --- Mouse Rotation Bonus --- */
int		handle_mouse_move_bonus(int x, int y, t_game *game);
void	init_mouse_bonus(t_game *game);

/* --- Wall Collision Bonus --- */
int		check_wall_bonus(t_game *game, int x, int y);
int		collision_detection_bonus(t_game *game);
void	move_bonus(t_game *game);

/* --- Player Movement Bonus (with collision) --- */
void	update_player_bonus(t_game *game);
void	update_player_speed_bonus(t_game *game);

/* --- Game Loop Bonus --- */
void	game_loop_bonus(t_game *game);
void	render_frame_bonus(t_game *game);

#endif
