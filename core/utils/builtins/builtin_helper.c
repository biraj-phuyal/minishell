/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:02:53 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/26 17:08:24 by biphuyal         ###   ########.fr       */
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
