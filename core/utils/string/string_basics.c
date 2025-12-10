/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_basics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:46:07 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/10 18:35:31 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}
size_t	strlen_double_array(char **env)
{
	size_t	len;

	len = 0;
	while (env[len] != NULL)
        len++;
	return (len);
}	

char	*ft_strdup(char *s)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
