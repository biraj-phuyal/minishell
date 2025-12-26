/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:09:11 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/26 17:00:57 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_one_command(t_cmd *cmd, t_env **env)
{
	if (is_builtin(cmd, 0))
		return (execute_builtin(cmd, 0, env));
	return (0);
}

int	execute(t_ast_node *ast, t_env **env, char **envp)
{
	(void)env;
	(void)envp;

	if (ast->type == NODE_CMD)
		return (execute_one_command(ast->cmd, env));
	return (0);
}
