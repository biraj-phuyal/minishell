/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:36:23 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/07 16:56:14 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_not_found(char *name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(": command not found", 2);
}

static void	child_dup(int in_fd, int out_fd)
{
	if (in_fd != -1)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != -1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

void	child_exec_cmd(t_exec_ctx *ctx, t_cmd *cmd, int in_fd, int out_fd)
{
	char	*cmd_path;

	child_dup(in_fd, out_fd);
	close_all_pipes(ctx);
	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd, 0))
	{
		execute_builtin(cmd, 0, ctx->env);
		return ;
	}
	cmd_path = path(*ctx->env, cmd->argv[0]);
	if (!cmd_path)
	{
		print_not_found(cmd->argv[0]);
		exit(127);
	}
	execve(cmd_path, cmd->argv, ctx->envp);
	free(cmd_path);
	exit(126);
}

pid_t	spawn_one(t_exec_ctx *ctx, t_cmd *cmd, int in_fd, int out_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		child_exec_cmd(ctx, cmd, in_fd, out_fd);
	return (pid);
}

void	get_fds(t_exec_ctx *ctx, int i, int count, int fd[2])
{
	fd[0] = -1;
	fd[1] = -1;
	if (i > 0)
		fd[0] = ctx->pipes[i - 1][0];
	if (i < count - 1)
		fd[1] = ctx->pipes[i][1];
}
