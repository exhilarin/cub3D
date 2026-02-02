/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pokemon_hud_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/02 00:00:00 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	draw_hud_scaled_image(t_game *game, t_img *img, int x,
		int y, float scale)
{
	int		i;
	int		j;
	int		color;
	char	*pixel;

	i = -1;
	while (++i < (int)(img->height * scale))
	{
		j = -1;
		while (++j < (int)(img->width * scale))
		{
			pixel = img->addr + ((int)(i / scale) * img->line_lenght
					+ (int)(j / scale) * (img->bpp / 8));
			color = *(unsigned int *)pixel;
			if ((color & 0x00FFFFFF) != 0x00FF00FF)
				mlx_pixel_put(game->mlx, game->win, x + j, y + i, color);
		}
	}
}

static char	*format_counter_string(int total, int collected)
{
	char	*total_str;
	char	*collected_str;
	char	*temp;
	char	*result;

	total_str = ft_itoa(total);
	if (!total_str)
		return (NULL);
	collected_str = ft_itoa(collected);
	if (!collected_str)
		return (free(total_str), NULL);
	temp = ft_strjoin(total_str, " / ");
	free(total_str);
	if (!temp)
		return (free(collected_str), NULL);
	result = ft_strjoin(temp, collected_str);
	free(temp);
	free(collected_str);
	return (result);
}

static void	draw_pokeball_icon(t_game *game, int x, int y, float scale)
{
	if (!game->pokeball_hud.img || !game->pokeball_hud.addr)
		return ;
	draw_hud_scaled_image(game, &game->pokeball_hud, x, y, scale);
}

void	draw_pokemon_counter_hud_bonus(t_game *game)
{
	char	*counter_text;
	int		scaled_size;
	int		icon_x;
	int		icon_y;

	if (!game->pokeball_hud.img || !game->pokeball_hud.addr)
		return ;
	scaled_size = (int)(game->pokeball_hud.width * 0.08);
	icon_x = LENGHT - scaled_size - 100;
	icon_y = 20;
	draw_pokeball_icon(game, icon_x, icon_y, 0.08);
	counter_text = format_counter_string(game->collected_pokemon,
			game->total_pokemon);
	if (!counter_text)
		return ;
	mlx_string_put(game->mlx, game->win, icon_x + scaled_size + 10,
		icon_y + (scaled_size / 2), 0x202020, counter_text);
	mlx_string_put(game->mlx, game->win, icon_x + scaled_size + 11,
		icon_y + (scaled_size / 2), 0x202020, counter_text);
	mlx_string_put(game->mlx, game->win, icon_x + scaled_size + 10,
		icon_y + (scaled_size / 2) + 1, 0x202020, counter_text);
	free(counter_text);
}

void	init_pokemon_counter_hud_bonus(t_game *game)
{
	game->pokeball_hud.img = mlx_xpm_file_to_image(game->mlx,
			"assets/sprites/pokeball/pokeball_score.xpm",
			&game->pokeball_hud.width,
			&game->pokeball_hud.height);
	if (game->pokeball_hud.img)
		game->pokeball_hud.addr = mlx_get_data_addr(game->pokeball_hud.img,
				&game->pokeball_hud.bpp, &game->pokeball_hud.line_lenght,
				&game->pokeball_hud.endian);
}
