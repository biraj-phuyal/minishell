/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:11:11 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/06 19:59:05 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pipe_cmd_count(t_ast_node *ast)
{
	int	count;

	if (!ast)
		return (0);
	count = 1;
	while (ast && ast->type == NODE_PIPE)
	{
		count++;
		ast = ast->left;
	}
	return (count);
}

int	pipe_fill_cmds(t_ast_node *ast, t_cmd **cmds, int count)
{
	int	i;

	if (!ast || !cmds || count <= 0)
		return (0);
	i = count - 1;
	while (ast && ast->type == NODE_PIPE && i > 0)
	{
		cmds[i] = ast->right->cmd;
		i--;
		ast = ast->left;
	}
	if (!ast || ast->type != NODE_CMD)
		return (0);
	cmds[0] = ast->cmd;
	return (1);
}

char	*read_pipe_content(int fd)
{
	char	*content;
	char	*temp;
	char	buffer[1024];
	int		bytes;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	while (1)
	{
		bytes = read(fd, buffer, 1023);
		if (bytes <= 0)
			break ;
		buffer[bytes] = '\0';
		temp = ft_strjoin(content, buffer);
		free(content);
		content = temp;
	}
	return (content);
}
