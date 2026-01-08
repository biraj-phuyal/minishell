/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:01:52 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/08 17:02:02 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_signal_received;

void	free_hd(t_heredoc *hd)
{
	if (hd->env)
		free_double_pointer(hd->env);
	if (hd->env_list)
		free_env(hd->env_list);
	if (hd->ast_root)
		ast_free(hd->ast_root);
}

int	handle_errors(char *line, t_heredoc *hd, int pipe_fd)
{
	if (g_signal_received == SIG_INTERRUPT_HEREDOC)
	{
		if (line)
			free(line);
		if (pipe_fd)
			close(pipe_fd);
		if (hd)
			free_hd(hd);
		return (130);
	}
	if (!line)
		return (130);
	if (ft_strcmp(line, hd->delim) == 0)
	{
		free(line);
		return (130);
	}
	return (0);
}