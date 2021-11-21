/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:28:42 by cyelena           #+#    #+#             */
/*   Updated: 2021/11/21 20:12:37 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# define BUF_SIZE 35

typedef struct get_next_line1
{
	int						fd;
	char					*r;
	struct get_next_line1	*next;
}	t_GNL;

t_GNL	*new_iinked_list(int fd);
int		get_next_line(int fd, char **line);
int		get_line(int fd, char **line, char **r);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strnew(size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_strcln(char *s);
#endif