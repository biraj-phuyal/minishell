/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:30:37 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/01 16:07:18 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

char	*remove_outer_quotes(const char *str)
{
	char	*result;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && (str[0] == '\'' || str[0] == '"') && str[0] == str[len - 1])
	{
		result = ft_substr(str, 1, len - 2);
		if (!result)
			return (NULL);
		return (result);
	}
	return (ft_strdup(str));
}
