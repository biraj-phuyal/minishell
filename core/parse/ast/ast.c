/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:30:00 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/06 21:59:27 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

/*
** Cria um novo nó de comando na AST
** @param cmd: estrutura de comando
** @return: novo nó ou NULL se erro
*/
t_ast_node	*ast_new_cmd(t_cmd *cmd)
{
	t_ast_node	*node;

	if (!cmd)
		return (NULL);
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	node->cmd = cmd;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/*
** Cria um novo nó de pipe na AST
** @param left: nó esquerdo (comando antes do pipe)
** @param right: nó direito (comando depois do pipe)
** @return: novo nó ou NULL se erro
*/
t_ast_node	*ast_new_pipe(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	if (!left || !right)
		return (NULL);
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->cmd = NULL;
	node->left = left;
	node->right = right;
	return (node);
}

/*
** Libera recursivamente a memória de um nó da AST
** @param node: nó a ser liberado
*/
void	ast_free(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD && node->cmd)
		cmd_free(node->cmd);
	else if (node->type == NODE_PIPE)
	{
		ast_free(node->left);
		ast_free(node->right);
	}
	free(node);
}
