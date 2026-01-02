/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:23:33 by biphuyal          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/01/03 18:09:50 by biphuyal         ###   ########.fr       */
=======
/*   Updated: 2026/01/02 15:27:17 by biphuyal         ###   ########.fr       */
>>>>>>> 0688264 (path joining for execve is working)
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	process_input(char *input, int last_status, t_env **env)
{
	t_ast_node	*ast;
	char		**envp;
	int			status;

	if (!input || !*input)
		return (last_status);
	envp = list_to_array(*env);
	ast = parse(input, last_status, envp);
	if (!ast)
	{
		free_double_pointer(envp);
		return (last_status);
	}
	status = execute(ast, env, envp);
<<<<<<< HEAD
	ast_free(ast);
	free_double_pointer(envp);
	if (status == 1)
		exit_program(*env);
=======
	if (status == 1)
	{
		ast_free(ast);
		free_double_pointer(envp);
		exit_program(*env);
	}
	ast_free(ast);
	free_double_pointer(envp);
>>>>>>> 0688264 (path joining for execve is working)
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
