/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:30:02 by yabokhar          #+#    #+#             */
/*   Updated: 2025/01/18 23:13:02 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static size_t	count_words(const char *str, char c)

{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (i == 0 || str[i - 1] == c)
		{
			if (str[i] != c)
				count++;
		}
		i++;
	}
	return (count);
}

static char	*loading_word(char const *s, char c)

{
	size_t	i;
	size_t	size;
	char	*word;

	size = 0;
	while (s[size] && s[size] != c)
		size++;
	word = malloc(sizeof(char) * (size + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < size)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**fill_array(char const *s, char c, char **array)

{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			array[j] = loading_word(&s[i], c);
			if (!array[j])
			{
				release_memory(array);
				return (NULL);
			}
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	array[j] = NULL;
	return (array);
}

char	**only_spaces_case(const char *s)

{
	char		**r;
	size_t		size;
	size_t		i;

	r = malloc(2 * sizeof(char *));
	if (!r)
		return (NULL);
	size = 0;
	while (s[size])
		size++;
	r[0] = malloc(sizeof(char) * size + 1);
	if (!r)
		return (NULL);
	i = 0;
	while (i < size)
	{
		r[0][i] = s[i];
		i++;
	}
	r[0][i] = '\0';
	r[1] = NULL;
	return (r);
}

char	**ft_split(char const *s, char c)

{
	size_t	size;
	char	**array;

	if (!s)
		return (NULL);
	if (ft_str_is_space(s))
	{
		array = only_spaces_case(s);
		return (array);
	}
	size = count_words(s, c);
	array = ft_calloc((size + 1), sizeof(char *));
	if (!array)
		return (NULL);
	array = fill_array(s, c, array);
	if (!array)
		return (NULL);
	return (array);
}
