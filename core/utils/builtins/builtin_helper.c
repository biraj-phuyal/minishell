/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:02:53 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/26 16:03:16 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_builtin(t_cmd *cmd, int i)
{
	if (cmd->argv[i] == "echo")
		return (true);
	else if (cmd->argv[i] == "export")
		return (true);
	else if (cmd->argv[i] == "unset")
		return (true);
	else if (cmd->argv[i] == "exit")
		return (true);
	else if (cmd->argv[i] == "cd")
		return (true);
	else if (cmd->argv[i] == "env")
		return (true);
	else if (cmd->argv[i] == "pwd")
		return (true);
	return (false);
}
