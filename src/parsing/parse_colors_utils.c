/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/01/27 01:08:30 by iguney           ###   ########.fr       */
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
	int		r;
	int		g;
	int		b;
	char	**a;

	a = malloc(sizeof(char *) * 4);
	a[3] = NULL;
	a[0] = ft_strtrim(rgb[0], " \t");
	a[1] = ft_strtrim(rgb[1], " \t");
	a[2] = ft_strtrim(rgb[2], " \t");
	if (ft_strchr(a[0], ' ') || ft_strchr(a[1], ' ') || ft_strchr(a[2], ' '))
		return (free_split(a), -1);
	r = ft_atoi(a[0]);
	g = ft_atoi(a[1]);
	b = ft_atoi(a[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_split(a), -1);
	return (free_split(a), (r << 16) | (g << 8) | b);
}
