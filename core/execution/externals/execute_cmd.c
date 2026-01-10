/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:36:23 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/10 20:16:15 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	child_cleanup(t_exec_ctx *ctx)
{
	if (ctx->ast)
		ast_free((t_ast_node *)ctx->ast);
	if (ctx->envp)
		free_double_pointer(ctx->envp);
	if (ctx->cmds)
		free(ctx->cmds);
	if (ctx->pids)
		free(ctx->pids);
	if (ctx->pipes)
		free(ctx->pipes);
	if (ctx->env && *ctx->env)
		free_env(*ctx->env);
	rl_clear_history();
}

void	child_dup(int in_fd, int out_fd)
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
static void	print_exec_error(char *cmd)
{
	write(2, "minishell: ", 11);
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	child_exec_cmd(t_cmd *cmd, t_exec_ctx *ctx)
{
	char	*cmd_path;
	int		status;

	default_signals();
	if (!cmd || !cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
	{
		child_cleanup(ctx);
		exit(0);
	}
	if (ctx && setup_redirections(cmd->redirs) != 0)
	{
		child_cleanup(ctx);
		exit(1);
	}
	if (is_builtin(cmd, 0))
	{
		status = execute_builtin(cmd, 0, ctx->env);
		child_cleanup(ctx);
		exit(status);
	}
	cmd_path = path(*ctx->env, cmd->argv[0]);
	if (!cmd_path)
	{
		write(2, "minishell: ", 11);
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, ": command not found\n", 20);
		child_cleanup(ctx);
		exit(127);
	}
	execve(cmd_path, cmd->argv, ctx->envp);
	print_exec_error(cmd->argv[0]);
	free(cmd_path);
	child_cleanup(ctx);
	exit(126);
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
