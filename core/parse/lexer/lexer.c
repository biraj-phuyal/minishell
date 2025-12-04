/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:53:48 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/04 15:09:29 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02                               #+#    #+#             */
/*   Updated: 2025/12/02                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

/*
** Inicializa a estrutura do lexer com os valores iniciais
** @param lex: ponteiro para a estrutura do lexer
** @param input: string de entrada a ser tokenizada
*/
void	lexer_init(t_lexer *lex, const char *input)
{
	lex->input = input;
	lex->pos = 0;
	lex->len = ft_strlen(input);
	lex->tokens = NULL;
}

/*
** Verifica se o caractere é um espaço em branco
*/
bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

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
** Retorna o caractere atual sem avançar
*/
char	current_char(t_lexer *lex)
{
	if (lex->pos >= lex->len)
		return ('\0');
	return (lex->input[lex->pos]);
}

/*
** Retorna o próximo caractere sem avançar (lookahead)
*/
char	peek_char(t_lexer *lex)
{
	if (lex->pos + 1 >= lex->len)
		return ('\0');
	return (lex->input[lex->pos + 1]);
}

/*
** Avança uma posição no input
*/
void	advance(t_lexer *lex)
{
	if (lex->pos < lex->len)
		lex->pos++;
}

/*
** Loop principal de tokenização
** Processa todo o input e cria a lista de tokens
** @return: true se sucesso, false se erro
*/
bool	lexer_tokenize(t_lexer *lex)
{
	char	c;

	while (lex->pos < lex->len)
	{
		skip_whitespace(lex);
		c = current_char(lex);
		if (c == '\0')
			break ;
		if (is_operator_char(c))
		{
			if (! tokenize_operator(lex))
				return (false);
		}
		else
		{
			if (!tokenize_word(lex))
				return (false);
		}
	}
	return (true);
}

/*
** Função principal do lexer
** Recebe uma string e retorna uma lista de tokens
** @param input: string de comando a ser analisada
** @return: lista ligada de tokens ou NULL se erro
*/
t_token	*lexer(const char *input)
{
	t_lexer	lex;
	t_token	*eof_token;

	if (!input)
		return (NULL);
	lexer_init(&lex, input);
	if (! lexer_tokenize(&lex))
	{
		token_list_free(lex.tokens);
		return (NULL);
	}
	eof_token = token_create(TOKEN_EOF, NULL);
	if (!eof_token || !token_add(&lex, eof_token))
	{
		token_list_free(lex. tokens);
		return (NULL);
	}
	return (lex.tokens);
}