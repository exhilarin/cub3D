/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:53:24 by agedikog          #+#    #+#             */
/*   Updated: 2026/01/27 00:51:34 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_max_width(t_game *game)
{
	int	i;
	int	len;

	i = 0;
	game->map.width = 0;
	while (game->map.grid[i])
	{
		len = ft_strlen(game->map.grid[i]);
		if (len > game->map.width)
			game->map.width = len;
		i++;
	}
	game->map.height = i;
}

static int	check_map_is_closed(char *map_str)
{
	int	i;

	i = 0;
	if (!map_str)
		return (1);
	while (map_str[i])
	{
		if (map_str[i] == '\n' && map_str[i + 1] == '\n')
			return (0);
		i++;
	}
	return (1);
}

static char	*init_map_str(char *first_line)
{
	char	*map_str;
	char	*temp;

	map_str = ft_strdup(first_line);
	if (!map_str)
		return (NULL);
	temp = ft_strjoin(map_str, "\n");
	free(map_str);
	return (temp);
}

static char	*read_map_lines(char *map_str, int fd)
{
	char	*line;
	char	*temp;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = ft_strjoin_gnl(map_str, line);
		free(line);
		if (!temp)
		{
			free(map_str);
			return (NULL);
		}
		map_str = temp;
	}
	return (map_str);
}

int	parse_map(char *first_line, int fd, t_game *game)
{
	char	*map_str;

	map_str = init_map_str(first_line);
	if (!map_str)
		return (0);
	map_str = read_map_lines(map_str, fd);
	if (!map_str)
		return (0);
	if (!check_map_is_closed(map_str))
	{
		free(map_str);
		free_game(game);
		ft_perror("Error\nEmpty line inside map detected\n");
	}
	game->map.grid = ft_split(map_str, '\n');
	free(map_str);
	if (!game->map.grid)
		return (0);
	get_max_width(game);
	return (1);
}
