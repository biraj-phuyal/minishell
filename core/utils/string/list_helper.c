/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 21:32:13 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/12 16:14:29 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_key(const char *envp)
{
	char		*key;
	char		*temp;
	size_t		len;

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

char	*get_value(char *envp)
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
