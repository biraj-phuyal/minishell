/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:57:02 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/10 14:18:13 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_pwd(void)
{
	char	buffer[9999];

	return (ft_strdup(getcwd(buffer, 9999)));
}

t_env	*update_new_pwd(t_env *env)
{
	char	*pwd;

	pwd = get_pwd();
	if (!pwd)
		return (NULL);
	env->value = destroy_and_copy(env->value, pwd);
	if (!env->value)
	{
		free(pwd);
		return (NULL);
	}
	free(pwd);
	return (env);
}

t_env	*update_old_pwd(t_env *env, char *og_pwd)
{
	env->value = destroy_and_copy(env->value, og_pwd);
	if (!og_pwd)
		return (NULL);
	if (!env->value)
	{
		free(og_pwd);
		return (NULL);
	}
	free(og_pwd);
	return (env);
}

t_env	*create_new_pwd(t_env *env)
{
	char	*pwd;
	t_env	*new;
	char	*key;
	t_env	*head;
	char	*value;

	pwd = get_pwd();
	if (!pwd)
		return (NULL);
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (free_list(head), NULL);
	new->key = "PWD";
	new->value = pwd;
	push_back(&head, new);
	return (head);
}

t_env	*create_old_pwd(t_env *env, char *og_pwd)
{
	t_env	*new;
	char	*key;
	t_env	*head;
	char	*value;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (free_list(head), NULL);
	new->key = "OLDPWD";
	new->value = og_pwd;
	push_back(&head, new);
	return (head);
}
