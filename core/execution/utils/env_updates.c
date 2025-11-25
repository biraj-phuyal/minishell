/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_updates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:41:38 by biphuyal          #+#    #+#             */
/*   Updated: 2025/11/25 01:16:16 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

void	overwrite(t_env *env, char *key, char *value)
{
	t_env	*head;

	head = env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, key) == 0)
			head->value = destroy_and_copy(head->value, value);
		if (!head->value)
			free_exit(head, "Allocation failure");
		head = head->next;
	}
}

char	*destroy_and_copy(char *dest, char *src)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(ft_strlen(src) + 1);
	if (!new)
		return (NULL);
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (free(dest), new);
}

char	*return_value(t_env *env, char *key)
{
	t_env	*head;

	if (!env || !key)
		return (env);
	head = env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

t_env	*unset_node(t_env *env, char *key)
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
