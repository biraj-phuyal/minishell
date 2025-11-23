/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 17:20:13 by biphuyal          #+#    #+#             */
/*   Updated: 2025/11/23 21:14:51 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execution.h"

void	push_back(t_env *env, char *key, char *value)
{
	t_env	*head;

	head = env;
	if (head->next == NULL)
	{
		head->next->key = key;
		head->next->value = value;
		head = head->next;
		head->next = NULL;
	}
	while (head->next != NULL)
		head = head->next;
	if (head->next == NULL)
	{
		head->next->key = key;
		head->next->value = value;
		head = head->next;
		head->next = NULL;
	}
}

void	create_list(t_env *env, char *envp)
{
	char	*key;
	char	*value;
	t_env	*head;

	head = malloc(sizeof(t_env));
	if (!head)
		free_list(head, "Allocation failure");
	head = env;
	key = get_key(envp);
	if (!key)
		free_list(head, "Allocation failure");
	value = get_value(envp);
	if (!value)
		free_list(head, "Allocation failure");
	if (repeated(head, key))
	{
		overwrite_value(head, key, value);
		return ;
	}
	push_back(head, key, value);
}