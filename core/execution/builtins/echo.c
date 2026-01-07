/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 20:15:58 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/06 19:44:26 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv[i] && flag(cmd->argv[i]))
		i++;
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		if (cmd->argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!flag(cmd->argv[1]))
		ft_putstr_fd("\n", 1);
}
