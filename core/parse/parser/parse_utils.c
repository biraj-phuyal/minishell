/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 21:57:14 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/22 22:18:07 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

bool	parse_heredoc_redir(t_cmd *cmd, t_redir_type redir_type, char *value)
{
	char	*delim;
	bool	quoted;
	bool	ok;

	delim = NULL;
	quoted = strip_quotes_if_any(value, &delim);
	ok = parse_add_redir(cmd, redir_type, delim, quoted);
	free(delim);
	return (ok);
}

bool	parse_redir_one(t_parser *p, t_cmd *cmd)
{
	t_redir_type	redir_type;

	redir_type = token_to_redir_type(p->current->type);
	if (!parser_advance(p))
		return (false);
	if (!p->current || p->current->type != TOKEN_WORD)
	{
		parser_error(p, "syntax error: expected filename");
		return (false);
	}
	if (redir_type == REDIR_HEREDOC)
	{
		if (!parse_heredoc_redir(cmd, redir_type, p->current->value))
			return (false);
	}
	else
	{
		if (!parse_add_redir(cmd, redir_type, p->current->value, false))
			return (false);
	}
	parser_advance(p);
	return (true);
}

bool	strip_quotes_if_any(const char *str, char **out)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 2 && is_quote(str[0]) && str[len - 1] == str[0])
	{
		*out = ft_substr(str, 1, len - 2);
		return (true);
	}
	*out = ft_strdup(str);
	return (false);
}

bool	parse_add_redir(t_cmd *cmd, t_redir_type type, char *value, bool quoted)
{
	t_redir	*redir;

	redir = redir_create(type, value, quoted);
	if (!redir || !redir_add(cmd, redir))
	{
		if (redir)
			redir_free(redir);
		return (false);
	}
	return (true);
}
