/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:26:29 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/11 17:45:27 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	apply_dup2_close(int fd, int target)
{
	if (fd < 0)
		return (1);
	if (dup2(fd, target) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_redir_errors(t_redir *redirs)
{
	t_redir	*curr;

	curr = redirs;
	while (curr)
	{
		if (curr->type == REDIR_IN)
		{
			if (check_input_redir(curr))
				return (1);
		}
		else if (curr->type == REDIR_OUT || curr->type == REDIR_APPEND)
		{
			if (check_output_redir(curr))
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	apply_input_redir(t_redir *curr)
{
	int	fd;

	fd = open(curr->file, O_RDONLY);
	if (fd < 0)
		return (1);
	if (apply_dup2_close(fd, STDIN_FILENO))
		return (1);
	return (0);
}

int	handle_heredoc_redir(t_redir *redir)
{
	int	pipe_fd[2];

	pipe(pipe_fd);
	write(pipe_fd[1], redir->heredoc_content,
		ft_strlen(redir->heredoc_content));
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (0);
}

int	check_output_redir(t_redir *curr)
{
	int	fd;

	if (curr->type == REDIR_APPEND)
		fd = open(curr->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(curr->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_redir_error(curr->file);
		return (1);
	}
	close(fd);
	return (0);
}
