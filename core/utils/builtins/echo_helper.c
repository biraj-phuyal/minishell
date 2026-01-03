/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 21:36:36 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/26 21:52:03 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	flag(char *argv)
{
	int	i;

	i = 0;
	if (!argv || argv[i] != '-')
		return (false);
	i++;
	while (argv[i])
	{
		if (argv[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}
