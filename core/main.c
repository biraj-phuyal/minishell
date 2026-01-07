/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:48:46 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/06 19:00:50 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_signal_received = 0;

int	main(int args, char **argv, char **envp)
{
	t_env	*env;

	((void)args, (void)argv);
	setup_signals();
	env = init_env(envp);
	program_loop(env);
}
