/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agedikog <agedikog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:54:36 by agedikog          #+#    #+#             */
/*   Updated: 2025/12/21 17:08:02 by agedikog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_perror(const char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}
