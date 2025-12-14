/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agedikoglu <agedikoglu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 00:00:00 by agedikoglu        #+#    #+#             */
/*   Updated: 2025/12/05 00:00:00 by agedikoglu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** Haritanın geçerli olup olmadığını kontrol eder
** - Harita duvarlarla (1) çevrili olmalı
** - Sadece 1 tane oyuncu olmalı (N, S, E, W)
** - Flood fill algoritması ile açık alan kontrolü
** - Boşluk (space) karakterlerini doğru handle eder
*/
