/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:04:26 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/06 19:44:52 by biphuyal         ###   ########.fr       */
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

void	free_double_pointer(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
