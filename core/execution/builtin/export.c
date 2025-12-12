/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:02:41 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/12 12:47:31 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*export(t_env *env, char *args)
{
	t_env	*head;

	head = env;
	if (!args)
	{
		export_with_no_arguments(head);
		return ;
	}
	return (export_with_arguments(env, args));
}

t_env	*export_with_arguments(t_env *env, char *args)
{
	char	*key;
	char	*value;
	t_env	*new;

	key = get_key(args);
	if (!key)
		return ;
	value = get_value(args);
	if (!value)
		return ;
	new->key = key;
	new->value = value;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return(overwrite_value(env, key, value));
		if (env->next == NULL)
		{
			push_back(&env, new);
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}

void	export_with_no_arguments(t_env *env)
{
	int		i;
	char	**formated_env;

	i = 0;
	formated_env = format_env(list_to_array(env));
	if (!formated_env)
	{
		free(formated_env);
		return ;
	}
	while (formated_env[i])
	{
		ft_putstr(formated_env[i]);
		i++;
	}
}