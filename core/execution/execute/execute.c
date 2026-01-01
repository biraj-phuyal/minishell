/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:09:11 by biphuyal          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/01/03 10:15:27 by biphuyal         ###   ########.fr       */
=======
/*   Updated: 2025/12/31 20:43:11 by biphuyal         ###   ########.fr       */
>>>>>>> dc6fb4d (Happy new year)
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_multiple_commands(t_ast_node *ast, t_env **env, char **envp)
{
	t_ast_node	*node;

	node = ast;
	while (node->type == NODE_PIPE)
	{
		if (node->left->type == NODE_CMD)
		{
			multiple_command_helper(node, *env, envp);
		}
		node = node->right;
	}
	return (0);
}

int	execute_one_command(t_cmd *cmd, t_env **env, char **envp)
{
	char	*cmd_path;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (is_builtin(cmd, 0))
		return (execute_builtin(cmd, 0, env));
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
int	execute_multiple_command(t_ast_node *ast, t_env *env, char **envp, int pid)
{
	int	fds[2];
	char *main_path;
	
	main_path = path(env);
	if (ast->right != NULL)
	{
		pipe(fds);
		pid = fork();
		if (pid == 0)
		{
			close(fds[0]);
			dup2(fds[1], STDOUT_FILENO);

			execve(main_path, NULL, envp);
		}
	}
}

int	execute(t_ast_node *ast, t_env **env, char **envp)
{
<<<<<<< HEAD
	if (ast->type == NODE_CMD)
		return (execute_one_command(ast->cmd, env, envp));
	if (ast->type == NODE_PIPE)
		return (execute_multiple_commands(ast, env, envp));
=======
	int	i;
	int	pid;

	if (ast->type == NODE_CMD)
		return (execute_one_command(ast->cmd, env));
	i = 0;
	while (i < ast->cmd->argc)
	{
		execute_multiple_command(ast, *env, envp, pid);
		i++;
	}
>>>>>>> dc6fb4d (Happy new year)
	return (0);
}
