/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agedikoglu <agedikoglu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 00:00:00 by agedikoglu        #+#    #+#             */
/*   Updated: 2025/12/05 00:00:00 by agedikoglu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** F (Floor) ve C (Ceiling) renklerini parse eder
** RGB değerlerini virgül ile ayırır
** 0-255 arası değer kontrolü yapar
** Format: F 220,100,0
*/

static int check_isdigit(char *str)
{
    int i;
    int found_digit;

    i = 0;
    found_digit = 0;
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    if (!str[i])
        return (0);
    while (str[i] && str[i] != '\n')
    {
        if (!ft_isdigit(str[i]))
            found_digit = 1;
        else if (str[i] != ' ' && str[i] != '\t')
            return (0);
        i++;
    }
    return (found_digit);
}

static void free_split(char **tab)
{
    int i;

    i = 0;
    if (!tab)
        return ;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

static int split_len(char **tab)
{
    int len;

    len = 0;
    while (tab[len])
        len++;
    return (len);
}

static int calculate_rgb(char **rgb)
{
    int r;
    int g;
    int b;

    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (-1);
    return ((r << 16) | (g << 8) | b);
}

void parse_colors(char *line, t_game *game)
{
    int i;
    char **rgb;
    int color;

    i = 1;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    rgb = ft_split(&line[i], ',');
    if (!rgb)
        ft_perror("Error\nMalloc failed in coloer parsing\n");
    if (split_len(rgb) != 3)
    {
        free_split(rgb);
        ft_perror("Error\nInvalid color format (Must be R,G,B)\n");
    }
    if (!check_isdigit(rgb[0]) || !check_isdigit(rgb[1]) || !check_isdigit(rgb[2]))
    {
        free_split(rgb);
        ft_perror("Error\nColor values must be digits only\n");
    }
    color = calculate_rgb(rgb);
    free_split(rgb);
    if (color == -1)
        ft_perror("Error\nColor values must be in range 0-255\n");
    if (line[0] == 'F')
    {
        if (game->textures.floor_color != -1)
            ft_perror("Error\nDuplicate Floor color\n");
        game->textures.floor_color = color;
        game->textures.c_count++;
    }
    else if (line[0] == 'C')
    {
        if (game->textures.ceiling_color != -1)
            ft_perror("Error\nDuplicate Ceiling color\n");
        game->textures.ceiling_color = color;
        game->textures.c_count++;
    }
}
