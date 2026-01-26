/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/01/27 01:00:21 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = skip_whitespace(line);
	if (!line || line[i] == '\0')
		return (0);
	while (line[i])
	{
		if (!is_valid_map_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_texture_id(char *s)
{
	if ((s[0] == 'N' && s[1] == 'O') || (s[0] == 'S' && s[1] == 'O')
		|| (s[0] == 'W' && s[1] == 'E') || (s[0] == 'E' && s[1] == 'A'))
		return (s[2] == ' ' || s[2] == '\t');
	return (0);
}

int	is_color_id(char *s)
{
	return ((s[0] == 'F' || s[0] == 'C') && (s[1] == ' ' || s[1] == '\t'));
}

void	check_all_elements(t_game *game)
{
	if (!game->textures.north || !game->textures.south)
	{
		free_game(game);
		ft_perror("Error\nMissing texture (NO/SO)\n");
	}
	if (!game->textures.west || !game->textures.east)
	{
		free_game(game);
		ft_perror("Error\nMissing texture (WE/EA)\n");
	}
	if (game->textures.floor_color == -1)
	{
		free_game(game);
		ft_perror("Error\nMissing floor color (F)\n");
	}
	if (game->textures.ceiling_color == -1)
	{
		free_game(game);
		ft_perror("Error\nMissing ceiling color (C)\n");
	}
}
