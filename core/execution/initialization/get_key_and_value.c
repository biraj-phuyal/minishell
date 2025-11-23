/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key_and_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 17:54:56 by biphuyal          #+#    #+#             */
/*   Updated: 2025/11/23 18:42:18 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execution.h"

char	*get_key(char *envp)
{
	char	*key;
	int		len;

	len = ft_strlen(ft_strchr(envp, '='));
	key = ft_substr(envp, 0, len);
	return (key);
}
char	*get_value(char *envp)
{
	char	*temp;
	char	*value;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	temp = ft_strchr(envp, '=');
	len = ft_strlen(temp);
	value = malloc(len);
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
	value[len] = '\0';
	return (value);
}
