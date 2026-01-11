/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:00:00 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/11 17:56:02 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_exec_error(char *cmd)
{
	write(2, "minishell: ", 11);
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	handle_dir_error(char *cmd_name, t_exec_ctx *ctx)
{
	write(2, "minishell: ", 11);
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, ": Is a directory\n", 17);
	child_cleanup(ctx);
	exit(126);
}

void	handle_stat_error(char *cmd_name, struct stat *st, t_exec_ctx *ctx)
{
	if (S_ISDIR(st->st_mode))
		handle_dir_error(cmd_name, ctx);
	write(2, "minishell: ", 11);
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, ": Permission denied\n", 21);
	child_cleanup(ctx);
	exit(126);
}

void	handle_path_error(char *cmd_name, t_exec_ctx *ctx)
{
	struct stat	st;

	if (ft_strchr(cmd_name, '/'))
	{
		if (stat(cmd_name, &st) == 0)
			handle_stat_error(cmd_name, &st, ctx);
		write(2, "minishell: ", 11);
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": No such file or directory\n", 29);
		child_cleanup(ctx);
		exit(127);
	}
	write(2, "minishell: ", 11);
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, ": command not found\n", 20);
	child_cleanup(ctx);
	exit(127);
}

void	exec_with_path(char *cmd_path, t_cmd *cmd, t_exec_ctx *ctx)
{
	execve(cmd_path, cmd->argv, ctx->envp);
	print_exec_error(cmd->argv[0]);
	free(cmd_path);
	child_cleanup(ctx);
	exit(127);
}
