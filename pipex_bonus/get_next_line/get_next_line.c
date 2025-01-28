/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:44:56 by yabokhar          #+#    #+#             */
/*   Updated: 2025/01/21 18:15:12 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char		*get_next_line(int fd, char *limiter, int *i);
static void	set_to_null(char *buffer);
static void	shift(char *buffer);
static void	handle_eof(char *limiter, int i);
char		*handling(int bytes_read, char *line, char *limiter, int i);

char	*get_next_line(int fd, char *lim, int *i)

{
	static char	buffer[FD_MAX][BUFFER_SIZE + 1];
	int			b_read;
	char		*l;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	b_read = 1;
	l = duplicate(buffer[fd]);
	if (!l)
		return (NULL);
	while (b_read && !string_contains_newline(buffer[fd]))
	{
		b_read = read(fd, buffer[fd], BUFFER_SIZE);
		if (b_read <= 0)
			return (set_to_null(buffer[fd]), handling(b_read, l, lim, (*i)));
		buffer[fd][b_read] = '\0';
		l = concatenate(l, buffer[fd]);
		if (!l)
			return (NULL);
		(*i)++;
	}
	shift(buffer[fd]);
	if (!l[0])
		return (free(l), NULL);
	return (l);
}

void	handle_eof(char *limiter, int i)

{
	ft_printf("pipex: warning: here-document at line %d ", i);
	ft_printf("delimited by end-of-file (wanted `%s')\n", limiter);
	exit(EXIT_FAILURE);
}

char	*handling(int bytes_read, char *line, char *limiter, int i)

{
	if (bytes_read == 0)
		handle_eof(limiter, i);
	return (free(line), NULL);
}

static void	set_to_null(char *buffer)

{
	while (*buffer)
	{
		*buffer = '\0';
		buffer++;
	}
}

static void	shift(char *buffer)

{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i + j])
	{
		buffer[j] = buffer[i + j];
		j++;
	}
	buffer[j] = '\0';
}
