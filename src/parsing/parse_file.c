/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agedikoglu <agedikoglu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 00:00:00 by agedikoglu        #+#    #+#             */
/*   Updated: 2025/12/05 00:00:00 by agedikoglu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int is_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S'
            || c == 'E' || c == 'W' || c == ' ' || c == '\t');
}

static int is_map_line(char *line)
{
    int i;

    i = 0;
    if (line[0] == '\0' || !line)
        return (0);
    while (line[i])
    {
        if (!is_map_char(line[i]))
            return (0);
        i++;
    }
    return (1);
}

static int process_line(char *line, t_game *game)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line [i] == '\0' || line[i] == '\n')
        return (0);
    if (ft_strncmp(&line[i], "NO", 2) == 0 || ft_strncmp(&line[i], "SO", 2) == 0
        || ft_strncmp(&line[i], "WE", 2) == 0 || ft_strncmp(&line[i], "EA", 2) == 0)
        parse_textures(&line[i], game);
    else if (ft_strncmp(&line[i], "F", 1) == 0 || ft_strncmp(&line[i], "C", 1) == 0)
        parse_colors(&line[i], game);
    else if (is_map_line(line))
        return (1);
    else
        ft_perror("Error\nUnknown identifier in map file\n");
    return (0);
}

static void check_all_elements(t_game *game)
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

void parse_file(char *file, t_game *game)
{
    char *line;
    int map_found;

    game->map_path = file;
    game->map_fd = open(game->map_path, O_RDONLY);
    if (game->map_fd < 0)
        ft_perror("Error\nCould not open map file\n");
    map_found = 0;
    while (1)
	{
		line = get_next_line(game->map_fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (process_line(line, game))
		{
			map_found = 1;
			if (!parse_map(line, game->map_fd, game))
			{
				free(line);
				close(game->map_fd);
				ft_perror("Error\nMap parsing failed\n");
			}
			free(line);
			break ;
		}
		free(line);
	}
	close(game->map_fd);
	if (!map_found)
		ft_perror("Error\nNo map found in file\n");
    check_all_elements(game);
	validate_map(game);
}
