/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:09:11 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/11 19:23:19 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	setup_redirections(t_redir *redirs)
{
	t_redir	*curr;

	if (!redirs)
		return (0);
	if (check_redir_errors(redirs))
		return (1);
	curr = redirs;
	while (curr)
	{
		if (curr->type == REDIR_IN)
		{
			if (apply_input_redir(curr))
				return (1);
		}
		else if (curr->type == REDIR_OUT || curr->type == REDIR_APPEND)
		{
			if (handle_output_redir(curr))
				return (1);
		}
		else if (curr->type == REDIR_HEREDOC)
			handle_heredoc_redir(curr);
		curr = curr->next;
	}
	return (0);
}

int	execute_external_command(char *cmd_path, t_cmd *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		return (1);
	}
	if (pid == 0)
		execute_child_process(cmd_path, cmd, envp);
	free(cmd_path);
	return (wait_for_child(pid));
}

int	execute_one_command(t_cmd *cmd, t_env **env, char **envp)
{
	int		saved_stdin;
	int		saved_stdout;
	int		status;

	if (!cmd)
		return (0);
	if (!cmd->argv || !cmd->argv[0])
		return (no_command_redir(cmd));
	if (is_builtin(cmd, 0))
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (setup_redirections(cmd->redirs) != 0)
		{
			close_cmd_fds(saved_stdin, saved_stdout);
			return (1);
		}
		status = execute_builtin(cmd, 0, env);
		close_cmd_fds(saved_stdin, saved_stdout);
		return (status);
	}
	return (execute_one_external_command(cmd, env, envp));
}

int	execute_one_external_command(t_cmd *cmd, t_env **env, char **envp)
{
	char	*cmd_path;

	if (!cmd->argv[0] || cmd->argv[0][0] == '\0')
		return (0);
	cmd_path = path(*env, cmd->argv[0]);
	if (!cmd_path)
		return (handle_no_path(cmd->argv[0]));
	return (execute_external_command(cmd_path, cmd, envp));
}

int	execute(t_ast_node *ast, t_env **env, char **envp)
{
	if (ast->type == NODE_CMD)
		return (execute_one_command(ast->cmd, env, envp));
	if (ast->type == NODE_PIPE)
		return (execute_pipeline(ast, env, envp));
	return (0);
}
