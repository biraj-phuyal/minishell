/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:41:29 by biphuyal          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/12/23 15:03:34 by biphuyal         ###   ########.fr       */
=======
/*   Updated: 2025/12/23 16:05:45 by biphuyal         ###   ########.fr       */
>>>>>>> 4319948 (base of main-lopp is done)
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

char	ft_toupper(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

char	ft_tolower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
