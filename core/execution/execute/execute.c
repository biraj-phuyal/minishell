/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:09:11 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/08 19:33:35 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	setup_redirections(t_redir *redirs)
{
	t_redir	*curr;
	int		fd;

	curr = redirs;
	while (curr)
	{
		if (curr->type == REDIR_IN)
		{
			fd = open(curr->file, O_RDONLY);
			if (fd == -1)
				return (perror(curr->file), -1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (curr->type == REDIR_OUT || curr->type == REDIR_APPEND)
		{
			if (handle_output_redir(curr) == -1)
				return (-1);
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
	int		status;

	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, SIG_DFL);
		if (setup_redirections(cmd->redirs) == -1)
			exit(1);
		execve(cmd_path, cmd->argv, envp);
		perror("minishell");
		free(cmd_path);
		exit(126);
	}
	free(cmd_path);
	ignore_signals();
	waitpid(pid, &status, 0);
	restore_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_one_external_command(t_cmd *cmd, t_env **env, char **envp)
{
	char	*cmd_path;

	cmd_path = path(*env, cmd->argv[0]);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		return (127);
	}
	return (execute_external_command(cmd_path, cmd, envp));
}

int	execute_one_command(t_cmd *cmd, t_env **env, char **envp)
{
	int		saved_stdin;
	int		saved_stdout;
	int		status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (is_builtin(cmd, 0))
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (setup_redirections(cmd->redirs) == -1)
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

int	execute(t_ast_node *ast, t_env **env, char **envp)
{
	if (ast->type == NODE_CMD)
		return (execute_one_command(ast->cmd, env, envp));
	if (ast->type == NODE_PIPE)
		return (execute_pipeline(ast, env, envp));
	return (0);
}
