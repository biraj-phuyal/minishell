/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:46:25 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/26 17:35:53 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	move_back(t_env **env, char *old_pwd, char *new_dir)
{
	t_env	*curr;

	curr = *env;
	if (chdir("..") == -1)
	{
		printf("minishell: cd: %s: No such file or directory", new_dir);
		return ;
	}
	new_pwd(&curr, old_pwd);
}

void	move_to_relative_path(t_env **env, char *old_pwd, char *new_dir)
{
	t_env	*curr;
	char	*relative_path;

	(void)new_dir;
	curr = *env;
	relative_path = return_value(*env, "HOME");
	if (chdir(relative_path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory", new_dir);
		return ;
	}
	new_pwd(&curr, old_pwd);
}

void	move_to_previous_dir(t_env **env, char *old_pwd, char *new_dir)
{
	t_env	*curr;
	char	*oldpwd;

	(void)new_dir;
	curr = *env;
	oldpwd = return_value(*env, "OLDPWD");
	if (!oldpwd || oldpwd[0] == '\0')
	{
		print_pwd(*env);
		return ;
	}
	if (chdir(oldpwd) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", oldpwd);
		return ;
	}
	printf("%s\n", oldpwd);
	new_pwd(&curr, old_pwd);
}
