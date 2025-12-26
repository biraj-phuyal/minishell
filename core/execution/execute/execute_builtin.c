/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:00:47 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/26 17:47:11 by biphuyal         ###   ########.fr       */
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
		execute_export(cmd, cmd->argv);
	return (0);
}
