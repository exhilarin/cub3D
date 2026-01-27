/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/01/27 06:22:38 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	split_len(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

int	check_isdigit(char *str)
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

int	calculate_rgb(char **rgb)
{
	long	r;
	long	g;
	long	b;
	char	**a;

	a = malloc(sizeof(char *) * 4);
	a[3] = NULL;
	a[0] = ft_strtrim(rgb[0], " \t");
	a[1] = ft_strtrim(rgb[1], " \t");
	a[2] = ft_strtrim(rgb[2], " \t");
	if (ft_strchr(a[0], ' ') || ft_strchr(a[1], ' ') || ft_strchr(a[2], ' '))
		return (free_split(a), -1);
	if (!a[0][0] || !a[1][0] || !a[2][0])
		return (free_split(a), -1);
	r = atol(a[0]);
	g = atol(a[1]);
	b = atol(a[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_split(a), -1);
	return (free_split(a), (r << 16) | (g << 8) | b);
}

void	check_adjacent_commas(char *line, char **rgb, t_game *game)
{
	int	i;

	i = 1 + skip_whitespace(&line[1]);
	while (line[i])
	{
		if (line[i] == ',' && (line[i + 1] == ',' || line[i + 1] == '\0'))
		{
			free_split(rgb);
			free(line);
			free_game(game);
			ft_perror("Error\nInvalid color format (Must be R,G,B)\n");
		}
		i++;
	}
}

int	count_commas(char *line)
{
	int	i;
	int	count;

	i = 1 + skip_whitespace(&line[1]);
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	return (count);
}
