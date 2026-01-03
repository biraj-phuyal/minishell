/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:09:11 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/03 16:45:25 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pipe_cmd_count(t_ast_node *ast)
{
	int	count;

	if (!ast)
		return (0);
	count = 1;
	while (ast && ast->type == NODE_PIPE)
	{
		count++;
		ast = ast->left;
	}
	return (count);
}

int	pipe_fill_cmds(t_ast_node *ast, t_cmd **cmds, int count)
{
	int	i;

	if (!ast || !cmds || count <= 0)
		return (0);
	i = count - 1;
	while (ast && ast->type == NODE_PIPE && i > 0)
	{
		cmds[i] = ast->right->cmd;
		i--;
		ast = ast->left;
	}
	if (!ast || ast->type != NODE_CMD)
		return (0);
	cmds[0] = ast->cmd;
	return (1);
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
		return (execute_pipeline(ast, env, envp));
	return (0);
}
