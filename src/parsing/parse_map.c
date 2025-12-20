/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agedikoglu <agedikoglu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 00:00:00 by agedikoglu        #+#    #+#             */
/*   Updated: 2025/12/05 00:00:00 by agedikoglu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void get_max_width(t_game *game)
{
    int i;
    int len;

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

char *gnl_strjoin(char *s1, char *s2)
{
    char	*new_str;
    size_t	i;
    size_t	j;
    size_t	len1;
    size_t	len2;

    if (!s1)
        return (ft_strdup(s2));
    if (!s2)
        return (s1);
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    new_str = malloc(len1 + len2 + 1);
    if (!new_str)
        return (NULL);
    i = 0;
    while (i < len1)
    {
        new_str[i] = s1[i];
        i++;
    }
    j = 0;
    while (j < len2)
    {
        new_str[i + j] = s2[j];
        j++;
    }
    new_str[i + j] = '\0';
    free(s1);
    return (new_str);
}

static int check_map_is_closed(char *map_str)
{
    int i;

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

int parse_map(char *first_line, int fd, t_game *game)
{
    char *line;
    char *map_str;
    char *temp;

    map_str = ft_strdup(first_line);
    if (!map_str)
        return (0);
    temp = ft_strjoin(map_str, "\n");
    free(map_str);
    map_str = temp;
    if (!map_str)
        return (0);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        map_str = gnl_strjoin(map_str, line);
        free(line);
    }
    if (!check_map_is_closed(map_str))
    {
        free(map_str);
        ft_perror("Error\nEmpty line inside map detected\n");
    }
    game->map.grid = ft_split(map_str, '\n');
    free(map_str);
    if (!game->map.grid)
        return (0);
    get_max_width(game);
    return (1);
}
