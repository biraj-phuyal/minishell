/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:09:08 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/07 18:05:58 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_pwd(t_env *env)
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
			head->value = destroy_and_copy(head->value, pwd);
			if (!head->value)
			{
				free(pwd);
				return (NULL);
			}
			ft_putstr(head->value);
		}
		head = head->next;
	}
}

t_env	*new_pwd(t_env *env, char *og_pwd)
{
	t_env	*head;
	char	*pwd;

	if (!env)
		return (NULL);
	pwd = get_pwd();
	if (!pwd)
		return (NULL);
	old_pwd(env, og_pwd);
	head = env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, "PWD") == 0)
		{
			env = update_new_pwd(head, pwd);
			return (env);
		}
		if (head->next == NULL)
		{
			env = create_new_pwd(head, pwd);
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
			env = update_old_pwd(head, og_pwd);
			return (env);
		}
		if (head->next == NULL)
		{
			env = create_new_pwd(head, og_pwd);
			return (env);
		}
		head = head->next;
	}
	return (env);
}