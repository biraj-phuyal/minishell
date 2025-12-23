/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:04:26 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/23 20:14:51 by biphuyal         ###   ########.fr       */
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
	t_env	*next;

	if (!env)
		return ;

	while (env != NULL)
	{
		next = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = next;
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
