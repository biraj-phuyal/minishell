/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 21:32:13 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/04 20:09:21 by biphuyal         ###   ########.fr       */
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
		return (NULL);
	len = ft_strlen(envp) - ft_strlen(temp);
	key = ft_substr(envp, 0, len);
	return (key);
}

char	*get_value(char *envp)
{
	char *equals;

	equals = ft_strchr(envp, '=');
	if (!equals)
		return (NULL);
	return (ft_strdup(equals + 1));
}
