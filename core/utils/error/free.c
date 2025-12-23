/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:04:26 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/23 16:59:54 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	free_env(t_env *env)
{
	t_env	*head;
	t_env	*next;

	if (!env)
		return ;
	
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

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
