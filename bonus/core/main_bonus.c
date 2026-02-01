/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by iguney            #+#    #+#             */
/*   Updated: 2026/02/01 09:54:38 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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
	game_loop_bonus(&game);
	free_game(&game);
	return (0);
}
