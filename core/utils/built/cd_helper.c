/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:46:25 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/10 14:17:40 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	move_back(t_env *env, char *old_pwd)
{
	if (chdir("..") == -1)
		return ;
	new_pwd(env, old_pwd);
	free(old_pwd);
}

void	move_to_relative_path(t_env *env, char *old_pwd, char *new_dir)
{
	char	*relative_path;

	relative_path = return_value(env, "HOME");
	if (chdir(relative_path) == -1)
		return ;
	new_pwd(env, old_pwd);
	free(old_pwd);
	return ;
}

void	move_to_previous_dir(t_env *env, char *old_pwd)
{
	if (chdir(old_pwd) == -1)
		return ;
	new_pwd(env, old_pwd);
	free(old_pwd);
	return ;
}
