/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:54:38 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/26 19:54:36 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*unset(t_env *env, char *key)
{
	t_env	*prev;
	t_env	*curr;

	if (!env || !key)
		return (env);
	if (ft_strcmp(env->key, key) == 0)
		return (free_head_node(env));
	prev = env;
	curr = env->next;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			prev->next = curr->next;
			if (curr->key)
				free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	return (env);
}
