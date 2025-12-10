/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:30:00 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/10 21:55:08 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

/*
** Inicializa o expander
*/
static void	expander_init(t_expander *exp, const char *input,
	int exit_status, char **env)
{
	exp->input = input;
	exp->result = NULL;
	exp->pos = 0;
	exp->state = STATE_NORMAL;
	exp->exit_status = exit_status;
	exp->env = env;
}

/*
** Processa expansão de variável
*/
static char	*process_expansion(t_expander *exp)
{
	char	*var_value;

	exp->pos++;
	var_value = expand_variable(exp);
	if (!var_value)
		return (NULL);
	exp->result = append_str(exp->result, var_value);
	free(var_value);
	return (exp->result);
}

/*
** Expande um token, processando variáveis de ambiente
** @param token: token a expandir
** @param exit_status: último exit status ($?)
** @param env: variáveis de ambiente
** @return: token expandido ou NULL se erro
*/
char	*expand_token(const char *token, int exit_status, char **env)
{
	t_expander	exp;
	char		c;

	if (!token)
		return (NULL);
	expander_init(&exp, token, exit_status, env);
	while (token[exp.pos])
	{
		c = token[exp.pos];
		update_quote_state(&exp, c);
		if (c == '$' && exp.state != STATE_SINGLE
			&& token[exp.pos + 1] != '\0')
		{
			if (!process_expansion(&exp))
				return (NULL);
		}
		else
		{
			exp.result = append_char(exp.result, c);
			if (!exp.result)
				return (NULL);
			exp.pos++;
		}
	}
	return (exp.result);
}

/*
** Expande todos os tokens WORD da lista
** @param tokens: lista de tokens
** @param exit_status: último exit status
** @param env: variáveis de ambiente
** @return: true se sucesso, false se erro
*/
bool	expand_tokens(t_token *tokens, int exit_status, char **env)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD && current->value)
		{
			expanded = expand_token(current->value, exit_status, env);
			if (!expanded)
				return (false);
			free(current->value);
			current->value = expanded;
		}
		current = current->next;
	}
	return (true);
}
