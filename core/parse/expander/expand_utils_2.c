/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:18:37 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/01 13:57:37 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

static bool	is_quote_char(char c)
{
	return (c == '\'' || c == '"');
}

bool	is_var_char(char c, bool first)
{
	if (first)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

static bool	handle_quote_char(t_expander *exp, char c)
{
	if ((exp->state == STATE_NORMAL && (c == '\'' || c == '"'))
		|| (exp->state == STATE_SINGLE && c == '\'')
		|| (exp->state == STATE_DOUBLE && c == '"'))
	{
		handle_quote_toggle(exp, c);
		exp->pos++;
		return (true);
	}
	exp->result = append_char(exp->result, c);
	if (!exp->result)
		return (false);
	exp->pos++;
	return (true);
}

static bool	handle_nonquote_char(t_expander *exp, char c)
{
	if (c == '$' && exp->state != STATE_SINGLE
		&& exp->input[exp->pos + 1] != '\0')
	{
		if (!process_expansion(exp))
			return (false);
	}
	else
	{
		exp->result = append_char(exp->result, c);
		if (!exp->result)
			return (false);
		exp->pos++;
	}
	return (true);
}

bool	process_char(t_expander *exp, char c)
{
	if (is_quote_char(c))
		return (handle_quote_char(exp, c));
	else
		return (handle_nonquote_char(exp, c));
}
