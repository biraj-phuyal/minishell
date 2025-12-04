/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:09 by gude-and          #+#    #+#             */
/*   Updated: 2024/06/19 00:22:54 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_l;
	size_t	src_l;

	src_l = ft_strlen(src);
	if (!size)
		return (src_l);
	dst_l = ft_strlen(dst);
	if (size <= dst_l)
		return (size + src_l);
	while (*src && size > dst_l + 1)
		dst[dst_l++] = *src++;
	dst[dst_l] = '\0';
	return (ft_strlen(dst) + ft_strlen(src));
}
