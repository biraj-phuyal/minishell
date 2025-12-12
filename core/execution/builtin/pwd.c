/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:09:08 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/12 16:50:36 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_pwd(t_env *env)
{
	t_env	*head;
	char	*pwd;

	if (!env)
		return (NULL);
	head = env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, "PWD") == 0)
		{
			pwd = get_pwd();
			destroy_and_copy(&head->value, pwd);
			if (!head->value)
				return (free(pwd), NULL);
		}
		if (head->next == NULL)
		{
			head = create_new_pwd(head);
			if (!head)
				return (free(pwd), NULL);
		}
		ft_putstr(head->value);
		head = head->next;
	}
}

t_env	*new_pwd(t_env *env, char *og_pwd)
{
	t_env	*head;

	if (!env)
		return (NULL);
	env = old_pwd(env, og_pwd);
	head = env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, "PWD") == 0)
		{
			head = update_new_pwd(head);
			if (!head)
				return (NULL);
			return (env);
		}
		if (head->next == NULL)
		{
			head = create_new_pwd(head);
			if (!head)
				return (NULL);
			return (env);
		}
		head = head->next;
	}
	return (env);
}

t_env	*old_pwd(t_env *env, char *og_pwd)
{
	t_env	*head;

	if (!env)
		return (NULL);
	head = env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, "OLDPWD") == 0)
		{
			head = update_old_pwd(head, og_pwd);
			if (!head)
				return (NULL);
			return (env);
		}
		if (head->next == NULL)
		{
			head = create_old_pwd(head, og_pwd);
			if (!head)
				return (NULL);
			return (env);
		}
		head = head->next;
	}
	return (env);
}
