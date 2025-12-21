/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:56:10 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/21 20:44:53 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static size_t	find_closing_quote(const char *str, size_t pos)
{
	char	quote_char;
	size_t	i;

	quote_char = str[pos];
	i = pos + 1;
	while (str[i])
	{
		if (str[i] == quote_char)
			return (i + 1);
		i++;
	}
	return (pos + 1);
}

size_t	skip_quoted_section(const char *str, size_t pos)
{
	if (! str || ! is_quote(str[pos]))
		return (pos + 1);
	return (find_closing_quote(str, pos));
}

char	*extract_quoted_content(const char *str, size_t *pos)
{
	size_t	start;
	size_t	end;
	char	*content;

	if (!str || !pos || !is_quote(str[*pos]))
		return (NULL);
	start = *pos;
	end = skip_quoted_section(str, start);
	content = ft_substr(str, start, end - start);
	*pos = end;
	return (content);
}
