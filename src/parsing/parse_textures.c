/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:53:36 by agedikog          #+#    #+#             */
/*   Updated: 2025/12/26 20:29:05 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_path(char *line, int i)
{
	char	*path;
	int		len;
	int		j;

	i += skip_whitespace(&line[i]);
	len = 0;
	while (line[i + len] && line[i + len] != '\n')
		len++;
	path = (char *)malloc(sizeof(char) * (len + 1));
	if (!path)
		return (NULL);
	j = 0;
	while (j < len)
	{
		path[j] = line[i + j];
		j++;
	}
	path[j] = '\0';
	return (path);
}

static void	assign_texture(char **dest, char *path, t_game *game)
{
	if (*dest != NULL)
	{
		free(path);
		ft_perror("Error\nDuplicate texture found\n");
	}
	*dest = path;
	game->textures.c_count++;
}

void	parse_textures(char *line, t_game *game)
{
	char	*path;

	path = get_path(line, 2);
	if (!path)
		ft_perror("Error\nMalloc failed in texture parsing\n");
	if (ft_strncmp(line, "NO", 2) == 0)
		assign_texture(&game->textures.north, path, game);
	else if (ft_strncmp(line, "SO", 2) == 0)
		assign_texture(&game->textures.south, path, game);
	else if (ft_strncmp(line, "WE", 2) == 0)
		assign_texture(&game->textures.west, path, game);
	else if (ft_strncmp(line, "EA", 2) == 0)
		assign_texture(&game->textures.east, path, game);
	else
	{
		free(path);
		ft_perror("Error\nUnknown texture identifier\n");
	}
}
