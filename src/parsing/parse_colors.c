/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:52:39 by agedikog          #+#    #+#             */
/*   Updated: 2026/01/27 01:08:30 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_rgb_format(char **rgb, t_game *game)
{
	if (split_len(rgb) != 3)
	{
		free_split(rgb);
		free_game(game);
		ft_perror("Error\nInvalid color format (Must be R,G,B)\n");
	}
	if (!check_isdigit(rgb[0]) || !check_isdigit(rgb[1])
		|| !check_isdigit(rgb[2]))
	{
		free_split(rgb);
		free_game(game);
		ft_perror("Error\nColor values must be digits only\n");
	}
}

static int	validate_and_get_color(char *line, t_game *game)
{
	int		i;
	char	**rgb;
	int		color;

	i = 1 + skip_whitespace(&line[1]);
	rgb = ft_split(&line[i], ',');
	if (!rgb)
	{
		free_game(game);
		ft_perror("Error\nMalloc failed in color parsing\n");
	}
	validate_rgb_format(rgb, game);
	color = calculate_rgb(rgb);
	free_split(rgb);
	if (color == -1)
	{
		free_game(game);
		ft_perror("Error\nColor values must be in range 0-255\n");
	}
	return (color);
}

void	parse_colors(char *line, t_game *game)
{
	int	color;

	color = validate_and_get_color(line, game);
	if (line[0] == 'F')
	{
		if (game->textures.floor_color != -1)
		{
			free_game(game);
			ft_perror("Error\nDuplicate Floor color\n");
		}
		game->textures.floor_color = color;
		game->textures.c_count++;
	}
	else if (line[0] == 'C')
	{
		if (game->textures.ceiling_color != -1)
		{
			free_game(game);
			ft_perror("Error\nDuplicate Ceiling color\n");
		}
		game->textures.ceiling_color = color;
		game->textures.c_count++;
	}
}
