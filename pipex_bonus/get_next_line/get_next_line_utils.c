/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:50:25 by yabokhar          #+#    #+#             */
/*   Updated: 2025/01/21 14:44:07 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

size_t	length_of(char *s, int newline_flag)

{
	size_t	bytes;

	bytes = 0;
	if (newline_flag)
	{
		while (s[bytes] && s[bytes] != '\n')
			bytes++;
		if (s[bytes] == '\n')
			bytes += 1;
		return (bytes);
	}
	while (s[bytes])
		bytes++;
	return (bytes);
}

int	string_contains_newline(char *s)

{
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char	*duplicate(char *s)

{
	size_t	size;
	size_t	i;
	char	*r;

	size = length_of(s, 1);
	r = malloc(sizeof(char) * (size + 1));
	if (!r)
		return (NULL);
	i = 0;
	while (i < size)
	{
		r[i] = s[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	*concatenate(char *line, char *buffer)

{
	size_t	buffer_size;
	size_t	i;
	size_t	j;
	char	*r;

	buffer_size = length_of(buffer, 1);
	r = malloc(sizeof(char) * (length_of(line, 0) + buffer_size + 1));
	if (!r)
		return (free(line), NULL);
	i = 0;
	while (line && line[i])
	{
		r[i] = line[i];
		i++;
	}
	j = 0;
	while (buffer && j < buffer_size)
	{
		r[i + j] = buffer[j];
		j++;
	}
	r[i + j] = '\0';
	free(line);
	return (r);
}
