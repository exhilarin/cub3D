/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agedikoglu <agedikoglu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 00:00:00 by agedikoglu        #+#    #+#             */
/*   Updated: 2025/12/05 00:00:00 by agedikoglu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** Hata mesajlarını yönetir
** "Error\n" ve açıklayıcı mesaj yazdırır
** Program'ı düzgün bir şekilde sonlandırır
** Örnek: error_exit("Invalid map format");
*/

void ft_perror(const char *str)
{
    if (str)
        write(2, str, ft_strlen(str));
    exit(EXIT_FAILURE);
}