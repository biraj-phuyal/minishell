/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:00:47 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/26 17:28:23 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_new_dir(t_cmd *cmd)
{
	char	*new_dir;
	int		i;

	i = 0;
	if (cmd->argc > 2)
		return (NULL);
	if (cmd->argv[1] == NULL)
	{
		new_dir = malloc(1);
		if (!new_dir)
			return (NULL);
		new_dir[0] = '\0';
		return (new_dir);
	}
	new_dir = malloc(ft_strlen(cmd->argv[1]) + 1);
	if (!new_dir)
		return (NULL);
	while (cmd->argv[1][i])
	{
		new_dir[i] = cmd->argv[1][i];
		i++;
	}
	new_dir[i] = '\0';
	return (new_dir);
}

void	execute_cd(t_cmd *cmd, int i, t_env **env) 
{
	char	*new_dir;

	if (ft_strcmp(cmd->argv[i], "cd") == 0)
	{
		new_dir = get_new_dir(cmd);
		if (!new_dir)
		{
			printf("minishell: cd: invalid arguments\n");
			return ;
		}
		change_dir(env, new_dir);
		free(new_dir);
		return ;
	}
}

int	execute_builtin(t_cmd *cmd, int i, t_env **env)
{
	if (ft_strcmp(cmd->argv[i], "cd") == 0)
	{
		execute_cd(cmd, i, env);
		return (0);
	}
	if (ft_strcmp(cmd->argv[i], "pwd") == 0)
	{
		print_pwd(*env);
		return (0);
	}
	return (0);
}
