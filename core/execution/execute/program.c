/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:23:33 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/09 20:26:15 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_signal_received;

static int	process_input(char *input, int last_status, t_env **env)
{
	t_ast_node	*ast;
	char		**envp;
	int			status;

	if (g_signal_received == SIGINT)
	{
		g_signal_received = 0;
		if (!input || !*input)
			return (130);
	}
	if (!input || !*input)
		return (last_status);
	envp = list_to_array(*env);
	ast = parse(input, last_status, envp, *env);
	if (!ast)
	{
		free_double_pointer(envp);
		if (g_signal_received == SIGINT)
		{
			g_signal_received = 0;
			return (130);
		}
		return (last_status);
	}
	status = execute(ast, env, envp);
	ast_free(ast);
	free_double_pointer(envp);
	if (status == 255)
		exit_program(*env);
	return (status);
}


void	program_loop(t_env *env)
{
	char	*input;
	int		last_status;

	last_status = 0;
	while (1)
	{
		input = readline("minishell: ");
		if (!input)
			free_list_and_exit(env);
		if (input)
			add_history(input);
		last_status = process_input(input, last_status, &env);
		free(input);
	}
}
