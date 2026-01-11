/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 21:32:13 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/11 18:11:09 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_key(const char *envp)
{
	char		*key;
	char		*temp;

	if (!envp)
		return (NULL);
	temp = ft_strchr(envp, '=');
	if (!temp)
		return (NULL);
	key = ft_substr(envp, 0, temp - envp);
	if (!key)
		return (NULL);
	return (key);
}

char	*get_value(const char *envp)
{
	char	*equals;
	char	*string;

	equals = ft_strchr(envp, '=');
	if (!equals)
		return (NULL);
	string = ft_strdup(equals + 1);
	if (!string)
		return (NULL);
	return (string);
}

static char	*allocate_empty_dir(void)
{
	char	*new_dir;

	new_dir = malloc(1);
	if (!new_dir)
		return (NULL);
	new_dir[0] = '\0';
	return (new_dir);
}

char	*get_new_dir(t_cmd *cmd)
{
	char	*new_dir;
	int		i;

	i = 0;
	if (cmd->argc > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (NULL);
	}
	if (cmd->argv[1] == NULL)
		return (allocate_empty_dir());
	new_dir = malloc(ft_strlen(cmd->argv[1]) + 1);
	if (!new_dir)
		return (NULL);
	while (cmd->argv[1][i])
	{
		new_dir[i] = cmd->argv[1][i];
		i++;
	}
	new_dir[i] = '\0';
	return (new_dir);
}
