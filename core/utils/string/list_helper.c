/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 21:32:13 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/12 12:34:06 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_key(char *envp)
{
	char		*key;
	char		*temp;
	ssize_t		len;

	temp = ft_strchr(envp, '=');
	if (!temp)
		return (free(temp), NULL);
	len = ft_strlen(envp) - ft_strlen(temp);
	key = ft_substr(envp, 0, len);
	if (!key)
		return (free(key), NULL);
	return (key);
}

char	*get_value(char *envp)
{
	char	*equals;
	char	*string;

	equals = ft_strchr(envp, '=');
	if (!equals)
		return (free(equals), NULL);
	string = ft_strdup(equals + 1);
	if (!string)
		return (free(string), NULL);
	return (string);
}
