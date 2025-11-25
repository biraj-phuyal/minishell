/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:04:26 by biphuyal          #+#    #+#             */
/*   Updated: 2025/11/25 01:15:36 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

void	free_exit(t_env *env, char *message)
{
	t_env	*head;
	t_env	*next;

	if (env)
	{
		head = env;
		while (head != NULL)
		{
			next = head->next;
			if (head->key)
				free(head->key);
			if (head->value)
				free(head->value);
			free(head);
			head = next;
		}
	}
	if (message)
		printf("%s", message);
	exit(EXIT_FAILURE);
}

t_env	*free_head_node(t_env *env)
{
	t_env	*first;

	if (!env)
		return (NULL);
	first = env->next;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
	return (first);
}
