/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 17:20:13 by biphuyal          #+#    #+#             */
/*   Updated: 2025/11/24 20:24:36 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execution.h"

t_env	*get_first_node(char *key, char *value)
{
	t_env	*head;

	head = malloc(sizeof(t_env));
	if (!head)
		exit(printf("Allocation failure"));
	head->key = key;
	head->value = value;
	head->exported = 1;
	head->next = NULL;
	return (head);
}

void	push_back(t_env *env, char *key, char *value)
{
	t_env	*head;

	while (env->next != NULL)
		env = env->next;
	if (env->next == NULL)
	{
		head = malloc(sizeof(t_env));
		if (!head)
			exit(printf("Allocation failure"));
		head->key = key;
		head->value = value;
		head->exported = 1;
		head->next = NULL;
		env->next = head;
		return ;
	}
}

t_env	*create_list(t_env *env, char *envp)
{
	char	*key;
	char	*value;

	key = get_key(envp);
	if (!key)
		free_list(env, "Allocation failure");
	value = get_value(envp);
	if (!value)
		free_list(env, "Allocation failure");
	if (!env)
		env = get_first_node(key, value);
	if (repeated(env, key))
	{
		overwrite_value(env, key, value);
		return (env);
	}
	push_back(env, key, value);
	return (env);
}