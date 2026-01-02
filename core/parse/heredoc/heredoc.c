/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 13:59:56 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/01 14:00:06 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static char	*append_line_to_content(char *content, char *expanded)
{
	char	*temp;

	temp = ft_strjoin(content, expanded);
	free(content);
	free(expanded);
	if (!temp)
		return (NULL);
	content = temp;
	temp = ft_strjoin(content, "\n");
	free(content);
	return (temp);
}

static char	*process_heredoc_line(char *line, char *content, t_heredoc *hd)
{
	char	*expanded;

	if (hd->expand)
		expanded = expand_heredoc_line(line, &hd->ctx);
	else
		expanded = ft_strdup(line);
	free(line);
	if (!expanded)
	{
		free(content);
		return (NULL);
	}
	return (append_line_to_content(content, expanded));
}

char	*read_heredoc(t_heredoc *hd)
{
	char	*line;
	char	*content;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, hd->delim) == 0)
		{
			free(line);
			break ;
		}
		content = process_heredoc_line(line, content, hd);
		if (!content)
			return (NULL);
	}
	return (content);
}

static bool	process_cmd_heredocs(t_cmd *cmd, t_heredoc *hd)
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
			hd->expand = ! redir->quoted;
			redir->heredoc_content = read_heredoc(hd);
			if (!redir->heredoc_content)
				return (false);
		}
		redir = redir->next;
	}
	return (true);
}

bool	process_heredocs(t_ast_node *ast, t_heredoc *hd)
{
	if (! ast)
		return (true);
	if (ast->type == NODE_CMD)
		return (process_cmd_heredocs(ast->cmd, hd));
	if (ast->type == NODE_PIPE)
	{
		if (!process_heredocs(ast->left, hd))
			return (false);
		if (!process_heredocs(ast->right, hd))
			return (false);
	}
	return (true);
}
