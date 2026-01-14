/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:41:09 by biphuyal          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2026/01/11 20:16:59 by biphuyal         ###   ########.fr       */
=======
/*   Updated: 2026/01/14 00:31:31 by biphuyal         ###   ########.fr       */
>>>>>>> Stashed changes
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
	ctx->cmds = run->cmds;
	ctx->pids = run->pids;
	ctx->cmd_count = run->count;
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
		{
			child_dup(fd[0], fd[1]);
			close_all_pipes(ctx);
			child_exec_cmd(run->cmds[i], ctx);
		}
		run->pids[i] = pid;
		i++;
	}
	return (1);
}

int	wait_last(pid_t *pids, int count)
{
	int	status;
	int	tmp_status;
	int	i;

	status = 0;
	if (count <= 0)
		return (0);
	i = 0;
	while (i < count)
	{
<<<<<<< Updated upstream
		waitpid(pids[i], &tmp_status, 0);
		if (i < count - 1 && WIFSIGNALED(tmp_status)
			&& WTERMSIG(tmp_status) == SIGPIPE)
			write(2, " Broken pipe\n", 13);
=======
>>>>>>> Stashed changes
		if (i == count - 1)
			status = tmp_status;
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
	ctx.cmds = NULL;
	ctx.pids = NULL;
	ctx.pipes = NULL;
	ctx.ast = (void *)ast;
	if (!setup_run(ast, &ctx, &run))
		return (1);
	if (!spawn_all(&ctx, &run))
		return (close_all_pipes(&ctx), free_run(&ctx, &run), 1);
	close_all_pipes(&ctx);
	ignore_signals();
	status = wait_last(run.pids, run.count);
	restore_signals();
	free_run(&ctx, &run);
	return (status);
}
