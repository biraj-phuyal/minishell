/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:23:25 by gude-and          #+#    #+#             */
/*   Updated: 2024/05/04 18:36:15 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	j;

	if (!big && !len)
		return (NULL);
	if (!*little)
		return ((char *)big);
	while (*big && len--)
	{
		j = 0;
		while (*(big + j) == *(little + j) && *(little + j) && j <= len)
		{
			if (!*(little + j + 1))
				return ((char *)big);
			j++;
		}
		big++;
	}
	return (NULL);
}
