/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:09:08 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/05 18:08:54 by biphuyal         ###   ########.fr       */
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

void	update_old_and_new_pwd(t_env *env, char *old_pwd)
{
	t_env	*head;
	char	*pwd;

	if (!env)
		return (NULL);
	head = env;
	update_old_pwd(env, old_pwd);
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

void	update_old_pwd(t_env *env, char *old_pwd)
{
	t_env	*head;

	if (!env)
		return (NULL);
	head = env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, "OLD_PWD") == 0)
		{
			head->value = destroy_and_copy(head->value, old_pwd);
			if (!head->value)
			{
				free(old_pwd);
				return (NULL);
			}
		}
		head = head->next;
	}
}