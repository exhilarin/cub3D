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

/*
** Ana .cub dosyasını açar ve parse eder
** Dosya uzantısı kontrolü yapar
** Dosyanın okunabilir olup olmadığını kontrol eder
*/

//map hariç her şey rastgele sırada olabilir
//bilgiler boşluk ve tab ile ayrılabilir

static void process_line(char *line, t_game *game)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line [i] == '\0' || line[i] == '\n')
        return ;
    if (ft_strncmp(&line[i], "NO", 2) == 0 || ft_strncmp(&line[i], "SO", 2) == 0
        || ft_strncmp(&line[i], "WE", 2) == 0 || ft_strncmp(&line[i], "EA", 2) == 0)
        parse_textures(&line[i], game);
    else if (ft_strncmp(&line[i], "F", 1) == 0 || ft_strncmp(&line[i], "C", 1) == 0)
        parse_colors(&line[i], game);
    else if ((line[i] == '0' || line[i] == '1'))
    {
        //parse_map(&line[i], game);
    }
    else
        ft_perror("Error\nUnknown identifier in map file\n");
    
}
 
//gnl ile satır okuma
//map argüman ile alınır

void parse_file(char *file, t_game *game)
{
    char *line;

    game->map_path = file;
    game->map_fd = open(game->map_path, O_RDONLY);
    if (game->map_fd < 0)
        ft_perror("Error\nCould not open map file\n");
    while (1)
    {
        line = get_next_line(game->map_fd);
        if (!line)
            break;
        if (line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';
        process_line(line, game);
        free(line);
    }
    close(game->map_fd);
}
