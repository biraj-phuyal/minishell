/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 13:59:56 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/08 17:01:29 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_signal_received;

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
		expanded = expand_heredoc_line(line, hd->exit_status, hd->env);
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

void	read_heredoc_loop(t_heredoc *hd, int pipe_fd)
{
	char	*line;
	char	*content;

	signal(SIGINT, handle_heredoc_sigint);
	content = ft_strdup("");
	if (!content)
		exit(1);
	while (1)
	{
		line = readline("> ");
		if (handle_errors(line, hd, 0))
			break ;
		content = process_heredoc_line(line, content, hd);
		if (!content)
			exit(1);
	}
	if (g_signal_received == SIG_INTERRUPT_HEREDOC)
		exit(handle_errors(content, 0, pipe_fd));
	write(pipe_fd, content, ft_strlen(content));
	free(content);
	close(pipe_fd);
	free_hd(hd);
	exit(0);
}

char	*handle_heredoc_child(int *fd, pid_t pid)
{
	int		status;
	char	*content;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_signal_received = SIG_INTERRUPT_HEREDOC;
		return (NULL);
	}
	content = read_pipe_content(fd[0]);
	return (content);
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
