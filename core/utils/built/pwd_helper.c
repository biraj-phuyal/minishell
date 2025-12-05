/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:57:02 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/05 19:29:20 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_pwd(void)
{
	char	buffer[9999];

	return(ft_strdup(getcwd(buffer, 9999)));
}

t_env	*update_new_pwd(t_env *env, char *pwd)
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
			head->value = destroy_and_copy(head->value, pwd);
			if (!head->value)
			{
				free(pwd);
				return (NULL);
			}
		}
		head = head->next;
	}
	return (env);
}

t_env	*update_old_pwd(t_env *env, char *pwd)
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
			head->value = destroy_and_copy(head->value, pwd);
			if (!head->value)
			{
				free(pwd);
				return (NULL);
			}
		}
		head = head->next;
	}
	return (env);
}