/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:04:26 by biphuyal          #+#    #+#             */
/*   Updated: 2025/11/24 17:21:37 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execution.h"

void	free_list(t_env *env, char *message)
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