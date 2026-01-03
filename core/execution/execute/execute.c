/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:09:11 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/03 10:15:27 by biphuyal         ###   ########.fr       */
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

int	execute(t_ast_node *ast, t_env **env, char **envp)
{
	if (ast->type == NODE_CMD)
		return (execute_one_command(ast->cmd, env, envp));
	if (ast->type == NODE_PIPE)
		return (execute_multiple_commands(ast, env, envp));
	return (0);
}
