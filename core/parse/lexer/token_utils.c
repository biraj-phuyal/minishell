/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:55:47 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/20 19:25:39 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"

void	token_free(t_token *token)
{
	if (! token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

void	token_list_free(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		token_free(current);
		current = next;
	}
}

t_token	*token_last(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

int	token_list_size(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

const char	*token_type_str(t_token_type type)
{
	static const char	*type_names[] = {
		"WORD",
		"PIPE",
		"REDIR_IN",
		"REDIR_OUT",
		"HEREDOC",
		"APPEND",
		"EOF"
	};

	if (type >= 0 && type <= TOKEN_EOF)
		return (type_names[type]);
	return ("UNKNOWN");
}
