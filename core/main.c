/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:48:46 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/10 19:01:41 by biphuyal         ###   ########.fr       */
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
	free_env(env);
	return (0);
}
