/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 21:15:34 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/07 18:13:02 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	change_dir(t_env *env, char	*new_dir)
{
	char	*old_pwd;
	char	*relative_path;

	old_pwd = get_pwd();
	if (!old_pwd)
		return ;
	if ((ft_strcmp(new_dir, "..") == 0))
	{
		if (chdir("..") == -1)
			return ;
		new_pwd(env, old_pwd);
		free(old_pwd);
		return ;
	}
	if (new_dir[0] == '\0')
	{
		relative_path = return_value(env, "HOME");
		if (chdir(relative_path) == -1)
			return ;
		new_pwd(env, old_pwd);
		free(old_pwd);
		return ;
	}
	if (chdir(new_dir) == -1)
		return ;
	new_pwd(env, old_pwd);
}