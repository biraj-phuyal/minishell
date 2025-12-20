/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:52:55 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/20 19:24:05 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdbool.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	const char	*input;
	size_t		pos;
	size_t		len;
	t_token		*tokens;
}	t_lexer;

/* lexer.c - Função principal */
t_token		*lexer(const char *input);
void		lexer_init(t_lexer *lex, const char *input);
bool		lexer_tokenize(t_lexer *lex);

/* tokenizer.c - Criação de tokens */
t_token		*token_create(t_token_type type, const char *value);
bool		token_add(t_lexer *lex, t_token *new_token);
bool		tokenize_operator(t_lexer *lex);
bool		tokenize_word(t_lexer *lex);

/* token_utils. c - Funções auxiliares */
void		token_free(t_token *token);
void		token_list_free(t_token *tokens);
t_token		*token_last(t_token *tokens);
int			token_list_size(t_token *tokens);
const char	*token_type_str(t_token_type type);

/* quotes.c - Gestão de aspas */
bool		is_quote(char c);
bool		quotes_are_closed(const char *str, size_t start);
size_t		skip_quoted_section(const char *str, size_t pos);
char		*extract_quoted_content(const char *str, size_t *pos);

/* Funções auxiliares gerais */
bool		is_operator_char(char c);
bool		is_whitespace(char c);
void		skip_whitespace(t_lexer *lex);
char		current_char(t_lexer *lex);
char		peek_char(t_lexer *lex);
void		advance(t_lexer *lex);

#endif
