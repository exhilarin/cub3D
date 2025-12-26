/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:58:27 by iguney            #+#    #+#             */
/*   Updated: 2025/12/26 04:54:11 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

int	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;
	char	*temp_s1;

	if (!s1)
	{
		temp_s1 = (char *)malloc(1 * sizeof(char));
		temp_s1[0] = '\0';
	}
	else
		temp_s1 = (char *)s1;
	if (!temp_s1 || !s2)
		return (NULL);
	str = (char *)malloc(ft_strlen_gnl(temp_s1) + ft_strlen_gnl(s2) + 1);
	i = -1;
	while (temp_s1[++i] != 0)
		str[i] = temp_s1[i];
	j = -1;
	while (s2[++j] != 0)
		str[i + j] = s2[j];
	str[i + j] = 0;
	free(temp_s1);
	return (str);
}
