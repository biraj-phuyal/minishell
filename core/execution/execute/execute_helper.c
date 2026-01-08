/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 10:13:47 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/08 16:13:26 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

void	close_pipe_pair(int fds[2])
{
	if (fds[0] != -1)
		close(fds[0]);
	if (fds[1] != -1)
		close(fds[1]);
}

void	close_all_pipes(t_exec_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->pipe_count)
	{
		close_pipe_pair(ctx->pipes[i]);
		i++;
	}
}

void	close_cmd_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	create_all_pipes(t_exec_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->pipe_count)
	{
		ctx->pipes[i][0] = -1;
		ctx->pipes[i][1] = -1;
		if (pipe(ctx->pipes[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}
