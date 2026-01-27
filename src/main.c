/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 21:04:49 by ilyas-guney       #+#    #+#             */
/*   Updated: 2026/01/27 06:01:08 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_file_extension(char *filename)
{
	char	*last_slash;
	char	*name;
	int		len;

	last_slash = ft_strrchr(filename, '/');
	if (last_slash)
		name = last_slash + 1;
	else
		name = filename;
	len = ft_strlen(name);
	if (len <= 4)
		return (0);
	return (ft_strncmp(&name[len - 4], ".cub", 4) == 0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		ft_perror("Error\nwrong number of arguments\n");
	if (!check_file_extension(argv[1]))
		ft_perror("Error\ninvalid file extension\n");
	init_data(&game);
	parse_file(argv[1], &game);
	game_loop(&game);
	free_game(&game);
	return (0);
}
