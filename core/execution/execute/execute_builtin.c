/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:00:47 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/26 20:14:36 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_builtin(t_cmd *cmd, int i, t_env **env)
{
	if (ft_strcmp(cmd->argv[i], "cd") == 0)
		execute_cd(cmd, i, env);
	else if (ft_strcmp(cmd->argv[i], "pwd") == 0)
		print_pwd(*env);
	else if (ft_strcmp(cmd->argv[i], "export") == 0)
		export(*env, cmd->argv[1]);
	else if (ft_strcmp(cmd->argv[i], "unset") == 0)
		*env = unset(*env, cmd->argv[i + 1]);
	else if (ft_strcmp(cmd->argv[i], "env") == 0)
		print_all_env(*env);
	else if (ft_strcmp(cmd->argv[i], "exit") == 0)
		return (1);
	return (0);
}
