/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:21:51 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/10 19:01:41 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_program(t_env *env)
{
	free_env(env);
	rl_clear_history();
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
