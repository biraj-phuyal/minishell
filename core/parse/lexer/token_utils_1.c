/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:55:47 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/11 20:08:40 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

bool	advance_quote(t_lexer *lex, char quote)
{
	ssize_t	new_pos;

	new_pos = skip_quoted_section(lex->input, lex->pos);
	if (new_pos == -1)
	{
		ft_putstr_fd(
			"minishell: unexpected EOF while looking for matching `", 2);
		ft_putchar_fd(quote, 2);
		ft_putstr_fd("'", 2);
		ft_putchar_fd('\n', 2);
		return (false);
	}
	lex->pos = new_pos;
	return (true);
}

bool	token_add(t_lexer *lex, t_token *new_token)
{
	t_token	*last;

	if (!new_token)
		return (false);
	if (!lex->tokens)
	{
		lex->tokens = new_token;
		return (true);
	}
	last = token_last(lex->tokens);
	last->next = new_token;
	return (true);
}
