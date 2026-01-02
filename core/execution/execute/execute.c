/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:09:11 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/02 16:45:58 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_one_command(t_cmd *cmd, t_env **env)
{
	if (is_builtin(cmd, 0))
		return (execute_builtin(cmd, 0, env));
	return (0);
}

int	execute_multiple_commands(t_ast_node *ast, t_env **env, char **envp)
{
	int	i;
	int	j;
	int	pid;
	int	fds[2];
	char *cmd_path;
	t_ast_node *node;

	i = 0;
	j = 0;
	node = ast;
	while (node == NODE_PIPE)
	{
		pipe(fds);
		if (node->left == NODE_CMD)
		{
			cmd_path = path(*env, node->cmd->argv[0]);
			if (!cmd_path)
				printf("%s: command not found", node->cmd->argv[0]);
			pid = fork();
			if (pid == 0)
			{
				dup2(fds[1], STDOUT_FILENO);

				execve(cmd_path, node->cmd->argv, envp);
			}
		}
		node = node->right;
	}
	if (node->right == NODE_CMD)
	{
		cmd_path = path(*env, node->cmd->argv[0]);
		if (!cmd_path)
			printf("%s: command not found", node->cmd->argv[0]);
		pipe(fds);
		pid = fork();
		if (pid == 0)
		{
			dup2(fds[0], STDIN_FILENO);

			execve(cmd_path, node->cmd->argv, envp);
		}
	}
	return (0);
}

int	execute(t_ast_node *ast, t_env **env, char **envp)
{
	if (ast->type == NODE_CMD)
		return (execute_one_command(ast->cmd, env));
	if (!(execute_multiple_commands(ast, env, envp)));
		
	return (0);
}
