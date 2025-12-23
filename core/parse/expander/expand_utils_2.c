/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:18:37 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/23 15:19:53 by biphuyal         ###   ########.fr       */
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

bool	process_char(t_expander *exp, char c)
{
	if (is_quote_char(c))
	{
		handle_quote_toggle(exp, c);
		exp->pos++;
	}
	else if (c == '$' && exp->state != STATE_SINGLE
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
