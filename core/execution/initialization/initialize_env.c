/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:32:15 by biphuyal          #+#    #+#             */
/*   Updated: 2025/11/23 17:57:58 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execution.h"

t_env	*init_env(char **envp)
{
	t_env	*head;
	int		i;

	i = 0;
	head = NULL;
	while (envp && envp[i])
	{
		create_list(head, envp[i]);
		i++;
	}
	return (head);
}