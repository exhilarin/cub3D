/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agedikog <agedikog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:53:11 by agedikog          #+#    #+#             */
/*   Updated: 2026/01/08 19:07:46 by agedikog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_line(char *line)
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

static int	is_texture_id(char *s)
{
	if ((s[0] == 'N' && s[1] == 'O') || (s[0] == 'S' && s[1] == 'O')
		|| (s[0] == 'W' && s[1] == 'E') || (s[0] == 'E' && s[1] == 'A'))
		return (s[2] == ' ' || s[2] == '\t');
	return (0);
}

static int	is_color_id(char *s)
{
	return ((s[0] == 'F' || s[0] == 'C') && (s[1] == ' ' || s[1] == '\t'));
}

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
		if (game->textures.c_count != 6)
			ft_perror("Error\nAll elements must be defined before map\n");
		return (1);
	}
	else
		ft_perror("Error\nUnknown identifier in map file\n");
	return (0);
}

static void	check_all_elements(t_game *game)
{
	if (!game->textures.north)
		ft_perror("Error\nMissing north texture (NO)\n");
	if (!game->textures.south)
		ft_perror("Error\nMissing south texture (SO)\n");
	if (!game->textures.west)
		ft_perror("Error\nMissing west texture (WE)\n");
	if (!game->textures.east)
		ft_perror("Error\nMissing east texture (EA)\n");
	if (game->textures.floor_color == -1)
		ft_perror("Error\nMissing floor color (F)\n");
	if (game->textures.ceiling_color == -1)
		ft_perror("Error\nMissing ceiling color (C)\n");
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
			map_found = 1;
			if (!parse_map(line, game->map_fd, game))
			{
				free(line);
				return (-1);
			}
			free(line);
			break ;
		}
		free(line);
	}
	return (map_found);
}

void	parse_file(char *file, t_game *game)
{
	int	result;
	int	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(&file[len - 4], ".cub", 4) != 0)
		ft_perror("Error\nMap file must have .cub extension\n");
	game->map_path = file;
	game->map_fd = open(game->map_path, O_RDONLY);
	if (game->map_fd < 0)
		ft_perror("Error\nCould not open map file\n");
	result = read_file_lines(game);
	close(game->map_fd);
	if (result == -1)
		ft_perror("Error\nMap parsing failed\n");
	if (result == 0)
		ft_perror("Error\nNo map found in file\n");
	check_all_elements(game);
	validate_map(game);
}
