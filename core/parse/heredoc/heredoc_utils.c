/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 14:00:30 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/07 14:55:37 by biphuyal         ###   ########.fr       */
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

char	*read_heredoc(t_heredoc *hd)
{
	int		fd[2];
	pid_t	pid;
	char	*content;

	if (pipe(fd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (NULL);
	}
	if (pid == 0)
	{
		close(fd[0]);
		read_heredoc_loop(hd, fd[1]);
	}
	close(fd[1]);
	content = handle_heredoc_child(fd, pid);
	close(fd[0]);
	return (content);
}

bool	process_cmd_heredocs(t_cmd *cmd, t_heredoc *hd)
{
	t_redir	*redir;

	if (!cmd)
		return (true);
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			hd->delim = redir->file;
			hd->expand = !redir->quoted;
			redir->heredoc_content = read_heredoc(hd);
			if (!redir->heredoc_content)
				return (false);
		}
		redir = redir->next;
	}
	return (true);
}
