/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agedikoglu <agedikoglu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 00:00:00 by agedikoglu        #+#    #+#             */
/*   Updated: 2025/12/05 00:00:00 by agedikoglu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char *get_path(char *line, int i)
{
    char *path;
    int len;
    int j;

    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
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

static void check_dup_texture(char *texture)
{
    if (texture != NULL)
        ft_perror("Error\nDuplicate texture found\n");
}

void parse_textures(char *line, t_game *game)
{
    char    *path;

    path = get_path(line, 2);
    if (!path)
        ft_perror("Error\nMalloc failed in texture parsing\n");
    if (ft_strncmp(line, "NO", 2) == 0)
    {
        check_dup_texture(game->textures.north);
        game->textures.north = path;
        game->textures.c_count++;   
    }
    else if (ft_strncmp(line, "SO", 2) == 0)
    {
        check_dup_texture(game->textures.south);
        game->textures.south = path;
        game->textures.c_count++;   
    }
    else if (ft_strncmp(line, "WE", 2) == 0)
    {
        check_dup_texture(game->textures.west);
        game->textures.west = path;
        game->textures.c_count++;   
    }
    else if (ft_strncmp(line, "EA", 2) == 0)
    {
        check_dup_texture(game->textures.east);
        game->textures.east = path;
        game->textures.c_count++;
    }
}
