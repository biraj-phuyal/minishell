/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:30:00 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/17 14:16:34 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <lexer.h>
# include <stdbool.h>

/*
** Estados de expansão para rastreamento de aspas
*/
typedef enum e_expand_state
{
	STATE_NORMAL,
	STATE_SINGLE,
	STATE_DOUBLE
}	t_expand_state;

/*
** Estrutura do expander
** Mantém o estado durante a expansão de variáveis
*/
typedef struct s_expander
{
	const char		*input;
	char			*result;
	size_t			pos;
	t_expand_state	state;
	int				exit_status;
	char			**env;
}	t_expander;

/* expander.c - Funções principais de expansão */
char	*expand_token(const char *token, int exit_status, char **env);
bool	expand_tokens(t_token *tokens, int exit_status, char **env);

/* expand_var.c - Expansão de variáveis */
char	*expand_variable(t_expander *exp);
char	*get_env_value(const char *name, char **env);
char	*extract_var_name(const char *str, size_t *len);

/* expand_utils.c - Funções auxiliares */
bool	is_var_char(char c, bool first);
char	*append_char(char *str, char c);
char	*append_str(char *s1, const char *s2);
void	update_quote_state(t_expander *exp, char c);

#endif
