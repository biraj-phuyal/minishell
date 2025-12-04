/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:04:26 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/04 16:58:10 by biphuyal         ###   ########.fr       */
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

void	fatal_envp_build(t_env *env, char **envp, int i, char *message)
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
	while (i--)
		free(envp[i]);
	if (message)
		printf("%s", message);
	exit(EXIT_FAILURE);
}
