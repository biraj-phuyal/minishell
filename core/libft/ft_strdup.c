/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:01:13 by gude-and          #+#    #+#             */
/*   Updated: 2024/06/19 19:01:54 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		l;

	l = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * l + 1);
	if (!dest)
		return (NULL);
	while (*s)
		*dest++ = *s++;
	*dest = '\0';
	return (dest - l);
}
