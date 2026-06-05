/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 19:01:26 by biphuyal          #+#    #+#             */
/*   Updated: 2026/02/03 23:00:21 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_signal_received;

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	g_signal_received = SIG_INTERRUPT_HEREDOC;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}
