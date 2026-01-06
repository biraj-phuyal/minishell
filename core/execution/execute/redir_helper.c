/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:26:29 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/06 17:29:14 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	handle_output_redir(t_redir *curr)
{
	int	fd;

	if (curr->type == REDIR_OUT)
	{
		fd = open(curr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror(curr->file), -1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (curr->type == REDIR_APPEND)
	{
		fd = open(curr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (perror(curr->file), -1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}
