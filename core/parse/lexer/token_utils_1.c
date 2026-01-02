/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:55:47 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/01 15:05:54 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

bool	advance_quote(t_lexer *lex, char quote)
{
	ssize_t	new_pos;

	new_pos = skip_quoted_section(lex->input, lex->pos);
	if (new_pos == -1)
	{
		ft_putstr_fd(
			"minishell: unexpected EOF while looking for matching `", 2);
		ft_putchar_fd(quote, 2);
		ft_putstr_fd("'", 2);
		ft_putchar_fd('\n', 2);
		return (false);
	}
	lex->pos = new_pos;
	return (true);
}
