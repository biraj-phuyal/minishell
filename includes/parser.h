/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:30:00 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/07 15:44:45 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "expander.h"
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env	t_env;

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
	char			*heredoc_content;
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
}	t_parser;

typedef struct s_heredoc
{
	const char	*delim;
	bool		expand;
	int			exit_status;
	char		**env;
	t_env		*env_list;
	struct s_ast_node	*ast_root;
}	t_heredoc;

t_cmd			*cmd_create(void);
void			cmd_free(t_cmd *cmd);
t_ast_node		*ast_new_cmd(t_cmd *cmd);
void			redir_free(t_redir *redir);
void			ast_free(t_ast_node *node);
void			syntax_error_newline(void);
bool			parser_advance(t_parser *p);
t_ast_node		*parse_command(t_parser *p);
t_ast_node		*parse_pipeline(t_parser *p);
bool			syntax_check(t_token *tokens);
void			syntax_error(const char *token);
bool			cmd_add_arg(t_cmd *cmd, char *arg);
bool			check_pipe_syntax(t_token *tokens);
bool			check_redir_syntax(t_token *tokens);
bool			redir_add(t_cmd *cmd, t_redir *redir);
t_redir_type	token_to_redir_type(t_token_type type);
bool			parse_redir_one(t_parser *p, t_cmd *cmd);
char			*handle_heredoc_child(int *fd, pid_t pid);
void			parser_error(t_parser *p, const char *msg);
bool			parse_command_loop(t_parser *p, t_cmd *cmd);
bool			parse_redirections(t_parser *p, t_cmd *cmd);
void			read_heredoc_loop(t_heredoc *hd, int pipe_fd);
bool			parser_expect(t_parser *p, t_token_type type);
bool			parse_add_redir(t_cmd *cmd, t_redir_type type,
					char *value, bool quoted);
bool			process_cmd_heredocs(t_cmd *cmd, t_heredoc *hd);
bool			strip_quotes_if_any(const char *str, char **out);
bool			process_heredocs(t_ast_node *ast, t_heredoc *hd);
t_ast_node		*ast_new_pipe(t_ast_node *left, t_ast_node *right);
char			*expand_heredoc_line(const char *line, int exit_status,
					char **env);
t_ast_node		*parse(const char *input, int exit_status, char **env,
					t_env *env_list);
t_redir			*redir_create(t_redir_type type, char *file, bool quoted);
void			parser_init(t_parser *p, t_token *tokens, int exit, char **env);

#endif
