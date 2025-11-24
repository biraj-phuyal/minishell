/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:41:38 by biphuyal          #+#    #+#             */
/*   Updated: 2025/11/24 20:59:12 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

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