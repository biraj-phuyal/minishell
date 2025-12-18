/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:39:05 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/18 23:20:45 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*command_line(t_token *token)
{
	t_command	*curr;

	curr = NULL;
	while (token)
	{
		push_back(&curr, token->value);
		handel_operators(token, &curr);
	}
}

void	handel_operators(t_token *token, t_command **curr)
{
	if (token->type == TOKEN_PIPE)
	{
		*curr = (*curr)->next;
		return ;
	}
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT || 
		token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
	{
		save_redir(token, curr);
		return ;
	}
}

void	save_redir(t_token *token, t_command *curr)
{
	if (token->type == TOKEN_REDIR_IN)
	{
		curr->identity = IN;
		return ;
	}
	else if (token->type == TOKEN_REDIR_OUT)
	{
		curr->identity = OUT;
		return ;
	}
	else if (token->type == TOKEN_APPEND)
	{
		curr->identity = APPEND;
		return ;
	}
	else if (token->type == TOKEN_HEREDOC)
	{
		curr->identity = HEREDOC;
		return ;
	}
}