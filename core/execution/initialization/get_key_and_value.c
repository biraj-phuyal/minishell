/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key_and_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 17:54:56 by biphuyal          #+#    #+#             */
/*   Updated: 2025/11/24 20:59:12 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

char	*get_key(char *envp)
{
	char	*key;
	char	*temp;
	int		len;

	temp = ft_strchr(envp, '=');
	if (!temp)
		return (NULL);
	len = ft_strlen(temp);
	key = ft_substr(envp, 0, len);
	return (key);
}
char	*get_value(char *envp)
{
	char	*temp;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = ft_strchr(envp, '=');
	value = malloc(ft_strlen(temp) + 1);
	if (!value)
		return (NULL);
	while(temp[i])
	{
		if (temp[0] == '=')
			i++;
		value[j] = temp[i];
		j++;
		i++; 	
	}
	value[j] = '\0';
	return (value);
}
