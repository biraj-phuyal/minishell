/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_funtions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:46:07 by biphuyal          #+#    #+#             */
/*   Updated: 2025/11/24 20:59:12 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*destroy_and_copy(char *dest, char *src)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(ft_strlen(src) + 1);
	if (!new)
		return (NULL);
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (free(dest), new);
}

char	*ft_substr(char *s, unsigned int start, int len)
{
	int		j;
	int		str_len;
	char	*string;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = str_len - start;
	string = (char *)malloc(len + 1);
	if (!string)
		return (NULL);
	j = 0;
	while (j < len && s[start + j])
	{
		string[j] = s[start + j];
		j++;
	}
	string[j] = '\0';
	return (string);
}
