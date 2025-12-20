/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:30:00 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/20 19:19:35 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "expander.h"
# include <stdbool.h>

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	bool			quoted;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char	**argv;
	int		argc;
	t_redir	*redirs;
}	t_cmd;

typedef struct s_ast_node
{
	t_node_type			type;
	t_cmd				*cmd;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_parser
{
	t_token	*tokens;
	t_token	*current;
	int		exit_status;
	char	**env;
	bool	error;
	char	*error_msg;
}	t_parser;

/* parser.c - Funções principais */
t_ast_node	*parse(const char *input, int exit_status, char **env);
void		parser_init(t_parser *p, t_token *tokens, int exit, char **env);
bool		parser_advance(t_parser *p);
bool		parser_expect(t_parser *p, t_token_type type);

/* parse_pipeline.c - Parsing de pipelines */
t_ast_node	*parse_pipeline(t_parser *p);

/* parse_cmd.c - Parsing de comandos */
t_ast_node	*parse_command(t_parser *p);
t_cmd		*cmd_create(void);
bool		cmd_add_arg(t_cmd *cmd, char *arg);
void		cmd_free(t_cmd *cmd);

/* parse_redir.c - Parsing de redirecionamentos */
bool		parse_redirections(t_parser *p, t_cmd *cmd);
t_redir		*redir_create(t_redir_type type, char *file, bool quoted);
bool		redir_add(t_cmd *cmd, t_redir *redir);
void		redir_free(t_redir *redir);

/* ast.c - Gerenciamento da AST */
t_ast_node	*ast_new_cmd(t_cmd *cmd);
t_ast_node	*ast_new_pipe(t_ast_node *left, t_ast_node *right);
void		ast_free(t_ast_node *node);

/* syntax_check.c - Validação de sintaxe */
bool		syntax_check(t_token *tokens);
bool		check_pipe_syntax(t_token *tokens);
bool		check_redir_syntax(t_token *tokens);

/* error.c - Gerenciamento de erros */
void		parser_error(t_parser *p, const char *msg);
void		syntax_error(const char *token);
void		syntax_error_newline(void);

#endif
