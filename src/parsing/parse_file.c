/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:53:11 by agedikog          #+#    #+#             */
/*   Updated: 2026/01/27 06:22:38 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	process_line(char *line, t_game *game)
{
	int	i;

	i = skip_whitespace(line);
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	if (is_texture_id(&line[i]))
		parse_textures(&line[i], game);
	else if (is_color_id(&line[i]))
		parse_colors(&line[i], game);
	else if (is_map_line(line))
	{
		if (game->textures.c_count == 6)
			return (1);
		free(line);
		free_game(game);
		ft_perror("Error\nAll elements must be defined before map\n");
	}
	else
	{
		free(line);
		free_game(game);
		ft_perror("Error\nUnknown identifier in map file\n");
	}
	return (0);
}

static int	parse_map_from_line(char *line, t_game *game)
{
	if (!parse_map(line, game->map_fd, game))
	{
		free(line);
		return (-1);
	}
	free(line);
	return (1);
}

static int	read_file_lines(t_game *game)
{
	char	*line;
	int		map_found;

	map_found = 0;
	while (1)
	{
		line = get_next_line(game->map_fd);
		if (!line)
			break ;
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (process_line(line, game))
		{
			map_found = parse_map_from_line(line, game);
			if (map_found == -1)
				return (-1);
			break ;
		}
		free(line);
	}
	return (map_found);
}

static void	validate_file_opening(char *file, t_game *game)
{
	char	*last_slash;
	char	*name;
	int		len;

	last_slash = ft_strrchr(file, '/');
	if (last_slash)
		name = last_slash + 1;
	else
		name = file;
	len = ft_strlen(name);
	if (len < 4 || ft_strncmp(&name[len - 4], ".cub", 4) != 0)
	{
		free_game(game);
		ft_perror("Error\nMap file must have .cub extension\n");
	}
	game->map_path = file;
	game->map_fd = open(game->map_path, O_RDONLY);
	if (game->map_fd < 0)
	{
		free_game(game);
		ft_perror("Error\nCould not open map file\n");
	}
}

void	parse_file(char *file, t_game *game)
{
	int	result;

	validate_file_opening(file, game);
	result = read_file_lines(game);
	close(game->map_fd);
	game->map_fd = -1;
	if (result == -1)
	{
		free_game(game);
		ft_perror("Error\nMap parsing failed\n");
	}
	if (result == 0)
	{
		free_game(game);
		ft_perror("Error\nNo map found in file\n");
	}
	check_all_elements(game);
	validate_map(game);
}
