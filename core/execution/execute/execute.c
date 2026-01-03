/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:09:11 by biphuyal          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2026/01/03 10:15:27 by biphuyal         ###   ########.fr       */
=======
/*   Updated: 2025/12/31 20:43:11 by biphuyal         ###   ########.fr       */
>>>>>>> dc6fb4d (Happy new year)
=======
/*   Updated: 2026/01/02 17:03:19 by biphuyal         ###   ########.fr       */
>>>>>>> 0688264 (path joining for execve is working)
=======
/*   Updated: 2026/01/03 10:31:26 by biphuyal         ###   ########.fr       */
>>>>>>> 1c7036d (path joining for execve is working)
=======
/*   Updated: 2026/01/03 16:45:25 by biphuyal         ###   ########.fr       */
>>>>>>> 7def5be (Some refactor is neccessary but otherwise pipes are  working)
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
	int	fds[2];
	char *main_path;
	
	main_path = path(*env, ast->cmd->argv[1]);
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

int	execute_multiple_commands(t_ast_node *ast, t_env **env, char **envp)
{
<<<<<<< HEAD
	if (ast->type == NODE_CMD)
		return (execute_one_command(ast->cmd, env, envp));
	if (ast->type == NODE_PIPE)
<<<<<<< HEAD
		return (execute_multiple_commands(ast, env, envp));
=======
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
>>>>>>> dc6fb4d (Happy new year)
	return (0);
}

int	execute(t_ast_node *ast, t_env **env, char **envp)
{
	if (ast->type == NODE_CMD)
		return (execute_one_command(ast->cmd, env));
	if (!(execute_multiple_commands(ast, env, envp)));
		
=======
		return (execute_pipeline(ast, env, envp));
>>>>>>> 7def5be (Some refactor is neccessary but otherwise pipes are  working)
	return (0);
}
