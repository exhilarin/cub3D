/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agedikog <agedikog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:52:39 by agedikog          #+#    #+#             */
/*   Updated: 2026/01/08 18:50:55 by agedikog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_isdigit(char *str)
{
	int	i;
	int	found_digit;

	found_digit = 0;
	i = skip_whitespace(str);
	if (!str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i] && str[i] != '\n')
	{
		if (ft_isdigit(str[i]))
			found_digit = 1;
		else if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (found_digit);
}

static int	split_len(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

static int	calculate_rgb(char **rgb)
{
	int	r;
	int	g;
	int	b;
	char **a;

	a = malloc(sizeof(char *) * 4);
	a[3] =NULL;
	a[0] = ft_strtrim(rgb[0], " \t");
	a[1] = ft_strtrim(rgb[1], " \t");
	a[2] = ft_strtrim(rgb[2], " \t");
	if (ft_strchr(a[0], ' ') || ft_strchr(a[1], ' ') || ft_strchr(a[2], ' ') )
		return (free_split(a), -1);
	r = ft_atoi(a[0]);
	g = ft_atoi(a[1]);
	b = ft_atoi(a[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_split(a), -1);
	return (free_split(a), (r << 16) | (g << 8) | b);
}

static int	validate_and_get_color(char *line)
{
	int		i;
	char	**rgb;
	int		color;

	i = 1 + skip_whitespace(&line[1]);
	rgb = ft_split(&line[i], ',');
	if (!rgb)
		ft_perror("Error\nMalloc failed in color parsing\n");
	if (split_len(rgb) != 3)
	{
		free_split(rgb);
		ft_perror("Error\nInvalid color format (Must be R,G,B)\n");
	}
	if (!check_isdigit(rgb[0]) || !check_isdigit(rgb[1])
		|| !check_isdigit(rgb[2]))
	{
		free_split(rgb);
		ft_perror("Error\nColor values must be digits only\n");
	}
	color = calculate_rgb(rgb);
	free_split(rgb);
	if (color == -1)
		ft_perror("Error\nColor values must be in range 0-255\n");
	return (color);
}

void	parse_colors(char *line, t_game *game)
{
	int	color;

	color = validate_and_get_color(line);
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
