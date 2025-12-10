/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:51:12 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/10 17:54:11 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**format_env(char **env)
{
	char	*key;
	int		i;

	while (env[i] != NULL)
	{
		key = get_key(env[i]);
		
	}
	
}