/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 00:00:00 by                   #+#    #+#             */
/*   Updated: 2026/01/11 20:08:45 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

t_token	*token_create(t_token_type type, const char *value, bool owned)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = NULL;
	token->has_quotes = false;
	token->next = NULL;
	if (value)
	{
		if (owned)
			token->value = (char *)value;
		else
		{
			token->value = ft_strdup(value);
			if (!token->value)
			{
				free(token);
				return (NULL);
			}
		}
	}
	return (token);
}

bool	tokenize_operator(t_lexer *lex)
{
	t_token_type	type;
	t_token			*token;
	char			c;
	char			next;

	c = current_char(lex);
	next = peek_char(lex);
	if (c == '|')
		type = TOKEN_PIPE;
	else if (c == '<' && next == '<')
		type = TOKEN_HEREDOC;
	else if (c == '>' && next == '>')
		type = TOKEN_APPEND;
	else if (c == '<')
		type = TOKEN_REDIR_IN;
	else
		type = TOKEN_REDIR_OUT;
	token = token_create(type, NULL, false);
	if (!token)
		return (false);
	advance(lex);
	if (type == TOKEN_HEREDOC || type == TOKEN_APPEND)
		advance(lex);
	return (token_add(lex, token));
}

static bool	word_has_quotes(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (true);
		i++;
	}
	return (false);
}

static char	*extract_word(t_lexer *lex)
{
	size_t	start;
	size_t	end;
	char	*word;

	start = lex->pos;
	if (!advance_to_word_end(lex))
		return (NULL);
	end = lex->pos;
	if (end == start)
		return (NULL);
	word = ft_substr(lex->input, start, end - start);
	return (word);
}

bool	tokenize_word(t_lexer *lex)
{
	char	*word;
	t_token	*token;

	word = extract_word(lex);
	if (!word)
		return (false);
	token = token_create(TOKEN_WORD, word, true);
	if (!token)
		return (false);
	token->has_quotes = word_has_quotes(word);
	return (token_add(lex, token));
}
