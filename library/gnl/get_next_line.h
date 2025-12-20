/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyas-guney <ilyas-guney@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:36 by iguney            #+#    #+#             */
/*   Updated: 2025/04/13 09:11:57 by ilyas-guney      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_update(char *putline);
char	*get_mainline(char *putline);
char	*get_read(int fd, char *putline);
char	*get_next_line(int fd);
char	*ft_strchr_gnl(const char *s, int c);
int		ft_strlen_gnl(const char *str);
char	*ft_strjoin_gnl(char const *s1, char const *s2);

#endif
