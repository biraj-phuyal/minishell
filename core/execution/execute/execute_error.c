/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:00:00 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/11 17:59:33 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_redir_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

int	check_input_redir(t_redir *curr)
{
	int	fd;

	fd = open(curr->file, O_RDONLY);
	if (fd < 0)
	{
		print_redir_error(curr->file);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_path_command_error(char *cmd_name, struct stat *st)
{
	if (S_ISDIR(st->st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putendl_fd(": Is a directory", 2);
		return (126);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putendl_fd(": Permission denied", 2);
	return (126);
}

int	handle_no_path(char *cmd_name)
{
	struct stat	st;

	if (ft_strchr(cmd_name, '/'))
	{
		if (stat(cmd_name, &st) == 0)
			return (handle_path_command_error(cmd_name, &st));
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}

int	wait_for_child(pid_t pid)
{
	int	status;

	ignore_signals();
	waitpid(pid, &status, 0);
	restore_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
