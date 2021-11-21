/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:25:16 by cyelena           #+#    #+#             */
/*   Updated: 2021/11/21 20:29:54 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*check_r(char *r, char **line)
{
	char	*p_n;

	p_n = NULL;
	if (r)
	{
		if ((p_n = ft_strchr(r, '\n')))
		{
			*p_n = '\0';
			*line = ft_strdup(r);
			ft_strlcpy(r, r, (size_t)++p_n);
		}
		else
		{
			*line = ft_strdup(r);
			ft_strcln(r);
		}
	}
	else
	{
		*line = ft_strnew(1);
	}
	return (p_n);
}

int	get_line(int fd, char **line, char **r)
{
	char		buf[BUF_SIZE + 1];
	int			byte_was_read;
	char		*p_n;
	char		*tmp;

	p_n = check_r(*r, line);
	while (!p_n && ((byte_was_read = read(fd, buf, BUF_SIZE))))
	{
		if ((p_n = ft_strchr(buf, '\n')))
		{
			*p_n = '\0';
			p_n++;
			*r = ft_strdup(p_n);
		}
		buf[byte_was_read] = '\0';
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buf)) || byte_was_read < 0)
			return (-1);
		free(tmp);
	}
	if (byte_was_read || ft_strlen(*line))
	{
		return (1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static t_GNL	*head;
	t_GNL			*tmp;

	if (fd < 0 ||line == NULL)
		return (-1);
	if (head == NULL)
		head = new_iinked_list(fd);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = new_iinked_list(fd);
		tmp = tmp->next;
	}
	return (get_line(tmp->fd, line, &tmp->r));
}

t_GNL	*new_iinked_list(int fd)
{
	t_GNL	*new;

	new = (t_GNL *)malloc(sizeof(t_GNL));
	new->fd = fd;
	new->r = NULL;
	new->next = NULL;
	return (new);
}

void	ft_strcln(char *s)
{
	if (s)
		while (*s)
			*s++ = '\0';
}

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s;
	size_t			i;

	s = b;
	i = 0;
	while (i < len)
	{
		s[i] = c;
		i++;
	}
	return (s);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	char	*s1;

	s1 = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!s1)
		return (NULL);
	ft_strlcpy(s1, s, ft_strlen(s) + 1);
	return (s1);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		k;

	k = 0;
	i = 0;
	if (!s1 || !s2)
		return (0);
	s = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(const char));
	if (!s)
		return (0);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[k])
	{
		s[i] = s2[k];
		i++;
		k++;
	}
	s[i] = '\0';
	return (s);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd1;
// 	int		fd2;
// 	int		counter;

// 	fd1 = open("text.txt", O_RDONLY);
// 	fd2 = open("text2.txt", O_RDONLY);
// 	counter = 0;
// 	while (get_next_line(fd1, &line) && counter < 3)
// 	{
// 		printf("%s\n", line);
// 		counter++;
// 	}
// 	while (get_next_line(fd2, &line) && counter < 7)
// 	{
// 		printf("%s\n", line);
// 		counter++;
// 	}
// 	while (get_next_line(fd1, &line) && counter < 9)
// 	{
// 		printf("%s\n", line);
// 		counter++;
// 	}
// 	// get_next_line(fd, &line);
// 	// printf("%s\n\n", line);
// // // 	// get_next_line(fd, &line);
// // // 	// printf("%s\n\n", line);
// // // 	// get_next_line(fd, &line);
// // // 	// printf("%s\n\n", line);
// // // 	// get_next_line(fd, &line);
// // // 	// printf("%s\n\n", line);
// // // 	// get_next_line(fd, &line);
// // // 	// printf("%s\n\n", line);
// // // 	// get_next_line(fd, &line);
// // // 	// printf("%s\n\n", line);
// // // 	// get_next_line(fd, &line);
// // // 	// printf("%s\n\n", line);
// // // 	// get_next_line(fd, &line);
// // // 	// printf("%s\n", line);
// }
