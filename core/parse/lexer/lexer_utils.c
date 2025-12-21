/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:30:00 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/20 19:24:40 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	skip_whitespace(t_lexer *lex)
{
	while (lex->pos < lex->len && is_whitespace(lex->input[lex->pos]))
		lex->pos++;
}

void	advance(t_lexer *lex)
{
	if (lex->pos < lex->len)
		lex->pos++;
}
