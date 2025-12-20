/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:47:17 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/20 19:24:51 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

void	syntax_error(const char *token)
{
	ft_putstr_fd((char *)"minishell: syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd((char *)token, 2);
	else
		ft_putstr_fd((char *)"newline", 2);
	ft_putendl_fd((char *)"'", 2);
}

void	syntax_error_newline(void)
{
	syntax_error("newline");
}

void	parser_error(t_parser *p, const char *msg)
{
	if (!p)
		return ;
	p->error = true;
	if (p->error_msg)
		free(p->error_msg);
	if (msg)
		p->error_msg = ft_strdup(msg);
	else
		p->error_msg = NULL;
}
