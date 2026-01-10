/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:02:53 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/10 23:06:14 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_builtin(t_cmd *cmd, int i)
{
	if ((ft_strcmp(cmd->argv[i], "echo") == 0))
		return (true);
	else if ((ft_strcmp(cmd->argv[i], "export") == 0))
		return (true);
	else if ((ft_strcmp(cmd->argv[i], "unset") == 0))
		return (true);
	else if ((ft_strcmp(cmd->argv[i], "exit") == 0))
		return (true);
	else if ((ft_strcmp(cmd->argv[i], "cd") == 0))
		return (true);
	else if ((ft_strcmp(cmd->argv[i], "env") == 0))
		return (true);
	else if ((ft_strcmp(cmd->argv[i], "pwd") == 0))
		return (true);
	return (false);
}

int	execute_builtin(t_cmd *cmd, int i, t_env **env)
{
	if (ft_strcmp(cmd->argv[i], "cd") == 0)
		return (execute_cd(cmd, i, env));
	else if (ft_strcmp(cmd->argv[i], "pwd") == 0)
		print_pwd(*env);
	else if (ft_strcmp(cmd->argv[i], "export") == 0)
		return (export(*env, cmd->argv[1]));
	else if (ft_strcmp(cmd->argv[i], "unset") == 0)
		*env = unset(*env, cmd->argv[i + 1]);
	else if (ft_strcmp(cmd->argv[i], "env") == 0)
		print_all_env(*env);
	else if (ft_strcmp(cmd->argv[i], "echo") == 0)
		echo(cmd);
	else if (ft_strcmp(cmd->argv[i], "exit") == 0)
		return (exit_builtin(cmd, *env));
	return (0);
}

int	execute_cd(t_cmd *cmd, int i, t_env **env)
{
	char	*new_dir;
	int		status;

	if (ft_strcmp(cmd->argv[i], "cd") == 0)
	{
		new_dir = get_new_dir(cmd);
		if (!new_dir)
			return (1);
		status = change_dir(env, new_dir);
		free(new_dir);
		return (status);
	}
	return (0);
}
