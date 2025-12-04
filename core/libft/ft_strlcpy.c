/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:52:49 by gude-and          #+#    #+#             */
/*   Updated: 2024/06/19 02:09:55 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*s;

	s = src;
	if (dst == NULL || !size)
		return (ft_strlen(src));
	while (*s && --size)
		*dst++ = *s++;
	*dst = '\0';
	return (ft_strlen(src));
}
