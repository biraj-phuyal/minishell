/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 21:15:34 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/11 17:35:30 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	handle_parent_dir(t_env **env, char *old_pwd, char *new_dir)
{
	move_back(env, old_pwd, new_dir);
	free(old_pwd);
	return (0);
}

static int	handle_empty_dir(t_env **env, char *old_pwd, char *new_dir)
{
	move_to_relative_path(env, old_pwd, new_dir);
	free(old_pwd);
	return (0);
}

static int	handle_previous_dir(t_env **env, char *old_pwd, char *new_dir)
{
	move_to_previous_dir(env, old_pwd, new_dir);
	free(old_pwd);
	return (0);
}

static int	handle_regular_dir(t_env **env, char *old_pwd, char *new_dir)
{
	if (chdir(new_dir) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(new_dir, 2);
		ft_putendl_fd(": No such file or directory", 2);
		free(old_pwd);
		return (1);
	}
	new_pwd(env, old_pwd);
	free(old_pwd);
	return (0);
}

int	change_dir(t_env **env, char *new_dir)
{
	char	*old_pwd;

	old_pwd = get_pwd();
	if (!old_pwd)
	{
		free(old_pwd);
		return (1);
	}
	if ((ft_strcmp(new_dir, "..") == 0))
		return (handle_parent_dir(env, old_pwd, new_dir));
	if (new_dir[0] == '\0')
		return (handle_empty_dir(env, old_pwd, new_dir));
	if (new_dir[0] == '-')
		return (handle_previous_dir(env, old_pwd, new_dir));
	return (handle_regular_dir(env, old_pwd, new_dir));
}
