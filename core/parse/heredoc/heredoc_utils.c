/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 14:00:30 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/04 17:11:14 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	init_expander(t_expander *exp, const char *line)
{
	exp->input = line;
	exp->result = NULL;
	exp->pos = 0;
	exp->state = STATE_NORMAL;
}

static char	*process_heredoc_char(t_expander *exp, const char *line)
{
	char	c;

	c = line[exp->pos];
	if (c == '$' && line[exp->pos + 1] != '\0')
	{
		if (! process_expansion(exp))
			return (NULL);
	}
	else
	{
		exp->result = append_char(exp->result, c);
		if (! exp->result)
			return (NULL);
		exp->pos++;
	}
	return (exp->result);
}

char	*expand_heredoc_line(const char *line, int exit_status, char **env)
{
	t_expander	exp;

	if (!line)
		return (NULL);
	init_expander(&exp, line);
	exp.exit_status = exit_status;
	exp.env = env;
	while (line[exp.pos])
	{
		if (! process_heredoc_char(&exp, line))
			return (NULL);
	}
	return (exp.result);
}
