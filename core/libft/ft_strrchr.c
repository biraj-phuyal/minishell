/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:57:36 by gude-and          #+#    #+#             */
/*   Updated: 2024/05/04 16:51:57 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		l;
	char	*str;

	l = ft_strlen(s);
	str = (char *)s;
	while (l >= 0)
	{
		if (s[l] == (char)c)
			return (&str[l]);
		l--;
	}
	return (NULL);
}
