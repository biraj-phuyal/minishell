/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 21:10:11 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/04 20:46:32 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	repeated(t_env *env, char *key)
{
	t_env	*head;

	head = env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (true);
		head = head->next;
	}
	return (false);
}

int	full_length_of_list(t_env *env)
{
	t_env	*head;
	int		i;

	head = env;
	i = 0;
	while (head != NULL)
	{
		i++;
		head = head->next;
	}
	return (i);
}
