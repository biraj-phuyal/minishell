/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 16:42:40 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/03 15:51:55 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*join_with_slash(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '/';
	i++;
	j = 0;
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

static char	*check_absolute_path(char *cmd)
{
	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

static char	*search_in_path(t_env *env, char *cmd)
{
	char	*cmd_path;
	char	**tmp_path;
	int		i;

	if (!return_value(env, "PATH"))
		return (NULL);
	tmp_path = ft_split((return_value(env, "PATH")), ':');
	i = -1;
	while (tmp_path[++i])
	{
		cmd_path = join_with_slash(tmp_path[i], cmd);
		if (access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	free_double_pointer(tmp_path);
	return (cmd_path);
}

char	*path(t_env *env, char *cmd)
{
	char	*result;

	if (!cmd || !cmd[0])
		return (NULL);
	result = check_absolute_path(cmd);
	if (result)
		return (result);
	return (search_in_path(env, cmd));
}