/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 10:13:47 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/03 10:15:03 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		execve(cmd_path, cmd->argv, envp);
		perror("minishell");
		free(cmd_path);
		exit(126);
	}
	free(cmd_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	multiple_command_helper(t_ast_node *node, t_env *env, char **envp)
{
	int			pid;
	int			new_pipe[2];
	int			prev_read;
	char		*main_path;

	prev_read = -1;
	pid = fork();
	if (pid == 0)
	{
		main_path = path(env, node->left->cmd->argv[0]);
		if (!main_path)
			printf("%s: command not found", node->left->cmd->argv[0]);
		pipe(new_pipe);
		if (prev_read != -1)
			dup2(new_pipe[0], STDIN_FILENO);
		dup2(new_pipe[1], STDOUT_FILENO);
		execve(main_path, node->left->cmd->argv, envp);
	}
	return (0);
}
