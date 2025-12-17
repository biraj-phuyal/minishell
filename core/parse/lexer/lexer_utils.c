/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:30:00 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/17 15:51:45 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

/*
** Verifica se o caractere é um operador do shell
*/
bool	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
** Avança a posição do lexer, pulando espaços em branco
*/
void	skip_whitespace(t_lexer *lex)
{
	while (lex->pos < lex->len && is_whitespace(lex->input[lex->pos]))
		lex->pos++;
}

/*
** Avança uma posição no input
*/
void	advance(t_lexer *lex)
{
	if (lex->pos < lex->len)
		lex->pos++;
}
