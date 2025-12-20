/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:19:37 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/20 19:25:11 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

static t_ast_node	*parse_pipe_next(t_parser *p, t_ast_node *left)
{
	t_ast_node	*right;
	t_ast_node	*pipe;

	right = parse_command(p);
	if (!right)
	{
		ast_free(left);
		return (NULL);
	}
	pipe = ast_new_pipe(left, right);
	if (!pipe)
	{
		ast_free(right);
		return (NULL);
	}
	return (pipe);
}

t_ast_node	*parse_pipeline(t_parser *p)
{
	t_ast_node	*left;

	left = parse_command(p);
	if (!left)
		return (NULL);
	while (p->current && p->current->type == TOKEN_PIPE)
	{
		if (!parser_advance(p))
		{
			ast_free(left);
			return (NULL);
		}
		left = parse_pipe_next(p, left);
		if (!left)
			return (NULL);
	}
	return (left);
}
