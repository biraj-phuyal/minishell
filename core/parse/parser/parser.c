/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 20:47:02 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/15 19:04:11 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/*
** Inicializa a estrutura do parser
** @param p: estrutura do parser
** @param tokens: lista de tokens
** @param exit: exit status anterior
** @param env: variáveis de ambiente
*/
void	parser_init(t_parser *p, t_token *tokens, int exit, char **env)
{
	p->tokens = tokens;
	p->current = tokens;
	p->exit_status = exit;
	p->env = env;
	p->error = false;
	p->error_msg = NULL;
}

/*
** Avança para o próximo token
** @param p: estrutura do parser
** @return: true se há mais tokens, false se fim ou erro
*/
bool	parser_advance(t_parser *p)
{
	if (!p || !p->current)
		return (false);
	if (p->current->type == TOKEN_EOF)
		return (false);
	p->current = p->current->next;
	return (true);
}

/*
** Verifica se o token atual é do tipo esperado
** @param p: estrutura do parser
** @param type: tipo esperado
** @return: true se match, false caso contrário
*/
bool	parser_expect(t_parser *p, t_token_type type)
{
	if (!p || !p->current)
		return (false);
	return (p->current->type == type);
}

/*
** Função principal de parsing
** INPUT → LEXER → SYNTAX CHECK → EXPANDER → PARSER → AST
** @param input: string de comando
** @param exit_status: exit status anterior
** @param env: variáveis de ambiente
** @return: AST ou NULL se erro
*/
t_ast_node	*parse(const char *input, int exit_status, char **env)
{
	t_token		*tokens;
	t_parser	parser;
	t_ast_node	*ast;

	tokens = lexer(input);
	if (!tokens)
		return (NULL);
	if (!syntax_check(tokens))
	{
		token_list_free(tokens);
		return (NULL);
	}
	if (!expand_tokens(tokens, exit_status, env))
	{
		token_list_free(tokens);
		return (NULL);
	}
	parser_init(&parser, tokens, exit_status, env);
	ast = parse_pipeline(&parser);
	token_list_free(tokens);
	if (parser.error_msg)
		free(parser.error_msg);
	return (ast);
}
