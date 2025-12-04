/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:30:24 by gude-and          #+#    #+#             */
/*   Updated: 2024/06/19 01:51:53 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *str, char c)
{
	int	words;
	int	separator;

	words = 0;
	separator = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != c && separator == 0)
		{
			separator = 1;
			words++;
		}
		else if (*str == c)
			separator = 0;
		str++;
	}
	return (words);
}

static char	*word_dup(const char *s, int start, int end)
{
	char	*word;
	size_t	i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

void	ft_free(char **str)
{
	while (*str)
	{
		free(*str);
		str++;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		word;
	int		start;
	char	**split;

	start = -1;
	i = -1;
	word = -1;
	split = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!split || !s)
		return (free(split), NULL);
	while (++i <= (int)ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == (int)ft_strlen(s)) && start >= 0)
		{
			split[++word] = word_dup(s, start, i);
			if (!split[word])
				return (ft_free(split), NULL);
			start = -1;
		}
	}
	split[++word] = 0;
	return (split);
}
