/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:00:00 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/11 19:23:21 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_output_redir(t_redir *curr)
{
	int	fd;

	if (curr->type == REDIR_APPEND)
		fd = open(curr->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(curr->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	if (apply_dup2_close(fd, STDOUT_FILENO))
		return (1);
	return (0);
}

void	execute_child_process(char *cmd_path, t_cmd *cmd, char **envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	if (setup_redirections(cmd->redirs) != 0)
		exit(1);
	execve(cmd_path, cmd->argv, envp);
	perror("minishell");
	free(cmd_path);
	exit(127);
}

int	no_command_redir(t_cmd *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	status = setup_redirections(cmd->redirs);
	close_cmd_fds(saved_stdin, saved_stdout);
	return (status);
}