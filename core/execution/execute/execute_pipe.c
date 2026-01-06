/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:41:09 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/06 19:44:07 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_run(t_exec_ctx *ctx, t_pipe_run *run)
{
	free(run->cmds);
	free(run->pids);
	free(ctx->pipes);
	run->cmds = NULL;
	run->pids = NULL;
	ctx->pipes = NULL;
}

int	setup_run(t_ast_node *ast, t_exec_ctx *ctx, t_pipe_run *run)
{
	run->count = pipe_cmd_count(ast);
	run->cmds = (t_cmd **)malloc(sizeof(t_cmd *) * run->count);
	run->pids = (pid_t *)malloc(sizeof(pid_t) * run->count);
	ctx->pipes = (int (*)[2])malloc(sizeof(int [2]) * (run->count - 1));
	if (!run->cmds || !run->pids || !ctx->pipes)
	{
		free_run(ctx, run);
		return (0);
	}
	ctx->pipe_count = run->count - 1;
	if (!pipe_fill_cmds(ast, run->cmds, run->count))
	{
		free_run(ctx, run);
		return (0);
	}
	if (!create_all_pipes(ctx))
	{
		free_run(ctx, run);
		return (0);
	}
	return (1);
}

int	spawn_all(t_exec_ctx *ctx, t_pipe_run *run)
{
	int		i;
	int		fd[2];
	pid_t	pid;

	i = 0;
	while (i < run->count)
	{
		get_fds(ctx, i, run->count, fd);
		pid = fork();
		if (pid < 0)
			return (0);
		if (pid == 0)
			child_exec_cmd(ctx, run->cmds[i], fd[0], fd[1]);
		run->pids[i] = pid;
		if (fd[0] != -1)
			close(fd[0]);
		if (fd[1] != -1)
			close(fd[1]);
		i++;
	}
	return (1);
}

int	wait_last(pid_t *pids, int count)
{
	int	status;
	int	i;

	status = 0;
	if (count <= 0)
		return (0);
	waitpid(pids[count - 1], &status, 0);
	i = 0;
	while (i < count - 1)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	return (get_exit_status(status));
}

int	execute_pipeline(t_ast_node *ast, t_env **env, char **envp)
{
	t_exec_ctx	ctx;
	t_pipe_run	run;
	int			status;

	run.cmds = NULL;
	run.pids = NULL;
	ctx.env = env;
	ctx.envp = envp;
	if (!setup_run(ast, &ctx, &run))
		return (1);
	if (!spawn_all(&ctx, &run))
		return (close_all_pipes(&ctx), free_run(&ctx, &run), 1);
	close_all_pipes(&ctx);
	status = wait_last(run.pids, run.count);
	free_run(&ctx, &run);
	return (status);
}
