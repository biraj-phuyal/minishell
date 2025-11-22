/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:32:15 by biphuyal          #+#    #+#             */
/*   Updated: 2025/11/22 21:39:38 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

t_env	*init_env(char **envp)
{
	t_env	*head;
	char	*value;
	char	*temp;
	int		len;
	char	*ep;
	int		i;

	i = 0;
	head = NULL;
	while (envp && envp[i])
	{
		ep = strchr(envp[i], '=')
		if (ep)
		{
			len = strlen(ep) - strlen(envp[i])
			value = stbstr(envp[i], 0, len);
			temp = strdup(ep);
		}
	}
}