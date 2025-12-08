/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:46:25 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/08 14:49:02 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	help_double_dot(t_env *env, char *old_pwd)
{
	if (chdir("..") == -1)
		return ;
	new_pwd(env, old_pwd);
	free(old_pwd);
}

void	help_relative_path(t_env *env, char *old_pwd, char *new_dir)
{
	char	*relative_path;

	if (new_dir[0] == '\0')
	{
		relative_path = return_value(env, "HOME");
		if (chdir(relative_path) == -1)
			return ;
		new_pwd(env, old_pwd);
		free(old_pwd);
		return ;
	}
}
