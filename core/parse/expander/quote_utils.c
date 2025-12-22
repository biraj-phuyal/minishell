/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:30:37 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/22 22:31:37 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

char	*remove_outer_quotes(const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 2 && (str[0] == '"' || str[0] == '\'') && str[len - 1] == str[0])
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}
