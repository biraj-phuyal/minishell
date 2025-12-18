/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:39:05 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/18 16:51:13 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*command_line(t_token *token)
{
	t_command	*curr;
	char		*redir;

	curr = NULL;
	while (token)
	{
		push_back(&curr, token->value);
		if (token->type == "TOKEN_PIPE")
			curr = curr->next;
		else if ((redir = is_redir(token)))
			break ;
	}
	
}
