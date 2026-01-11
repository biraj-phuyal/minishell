/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:04:26 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/10 19:01:41 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_list_and_exit(t_env *env)
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
	rl_clear_history();
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
