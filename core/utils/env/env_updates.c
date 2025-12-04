/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_updates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:41:38 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/04 19:53:30 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*overwrite_value(t_env *env, char *key, char *value)
{
	t_env	*head;

	head = env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, key) == 0)
			head->value = destroy_and_copy(head->value, value);
		if (!head->value)
		{
			free_list(head);
			return (NULL);
		}
		head = head->next;
	}
	return (env);
}

char	*destroy_and_copy(char *dest, char *src)
{
	char		*new;
	ssize_t		i;

	i = 0;
	new = malloc(ft_strlen(src) + 1);
	if (!new)
		return (NULL);
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (free(dest), new);
}

char	*return_value(t_env *env, char *key)
{
	t_env	*head;

	if (!env || !key)
		return (NULL);
	head = env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

t_env	*unset_node(t_env *env, char *key)
{
	t_env	*prev;
	t_env	*curr;

	if (!env || !key)
		return (env);
	if (ft_strcmp(env->key, key) == 0)
		return (free_head_node(env));
	prev = env;
	curr = env->next;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			prev->next = curr->next;
			if (curr->key)
				free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	return (env);
}

char	*join_key_value(char *key, char *value)
{
	size_t		i;
	size_t		size;
	char		*string;

	if (!key)
		return (NULL);
	size = ft_strlen(key);
	i = size;
	if (value)
		size += ft_strlen(value);
	string = ft_calloc(size + 2, sizeof(char));
	if (!string)
		return (NULL);
	ft_strcpy(string, key);
	string[i++] = '=';
	ft_strcpy(&string[i], value);
	return (string);
}
