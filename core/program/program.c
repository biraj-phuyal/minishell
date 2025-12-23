/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:23:33 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/03 18:08:19 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	program_loop(t_env *env)
{
	char		*input;
	t_ast_node	*ast;
	char		**envp;
	int			last_status;

	last_status = 0;
	while (1)
	{
		input = readline("minishell: ");
		if (!input)
			free_list_and_exit(env);
		if (input)
			add_history(input);
		envp = list_to_array(env);
		ast = parse(input, last_status, envp);
		free(input);
		if (!ast)
			continue ;
		last_status = execute(ast, &env, envp);
		ast_free(ast);
		free_envp(envp);
		if (last_status == 1)
			exit_program(env);
	}
}
