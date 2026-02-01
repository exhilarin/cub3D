/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 02:25:14 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_BONUS_H
# define MINIMAP_BONUS_H


/* Minimap configuration - Pokemon Theme */
# define MINIMAP_SIZE 200
# define MINIMAP_MARGIN 20
# define MINIMAP_BG_COLOR 0x90EE90
# define MINIMAP_WALL_COLOR 0x228B22
# define MINIMAP_PLAYER_COLOR 0xFF3030
# define MINIMAP_PLAYER_SIZE 5
# define MINIMAP_BORDER_COLOR 0x8B4513

/* Minimap initialization and drawing functions */
void	init_minimap(t_game *game, t_minimap *minimap);
void	draw_minimap(t_game *game, t_minimap *minimap);
void	draw_minimap_with_border(t_game *game, t_minimap *minimap);

#endif
