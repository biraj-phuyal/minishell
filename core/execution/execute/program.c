/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:23:33 by biphuyal          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/01/03 18:08:19 by biphuyal         ###   ########.fr       */
=======
/*   Updated: 2025/12/26 20:13:31 by biphuyal         ###   ########.fr       */
>>>>>>> e5eb1cc (exit is working)
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	process_input(char *input, int last_status, t_env **env)
{
	t_ast_node	*ast;
	char		**envp;
	int			status;

	envp = list_to_array(*env);
	ast = parse(input, last_status, envp);
	if (!ast)
	{
		free_envp(envp);
		return (last_status);
	}
	status = execute(ast, env, envp);
	if (status == 1)
	{
		ast_free(ast);
		free_envp(envp);
		exit_program(*env);
	}
	ast_free(ast);
	free_envp(envp);
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
