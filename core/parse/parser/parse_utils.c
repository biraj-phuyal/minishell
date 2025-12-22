/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 21:57:14 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/22 21:58:30 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

bool	parse_add_redir(t_cmd *cmd, t_redir_type type, char *value)
{
	t_redir	*redir;

	redir = redir_create(type, value, false);
	if (!redir || !redir_add(cmd, redir))
	{
		if (redir)
			redir_free(redir);
		return (false);
	}
	return (true);
}
