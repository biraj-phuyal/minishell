/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:30:00 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/10 21:55:12 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

/*
** Verifica se um caractere é válido em nome de variável
** @param c: caractere a verificar
** @param first: true se é o primeiro caractere do nome
*/
bool	is_var_char(char c, bool first)
{
	if (first)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

/*
** Adiciona um caractere ao final de uma string
** @param str: string original (será liberada)
** @param c: caractere a adicionar
** @return: nova string ou NULL se erro
*/
char	*append_char(char *str, char c)
{
	char	*new_str;
	size_t	len;

	if (!str)
	{
		new_str = malloc(2);
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	ft_memcpy(new_str, str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(str);
	return (new_str);
}

/*
** Concatena duas strings e libera a primeira
** @param s1: primeira string (será liberada)
** @param s2: segunda string (não será modificada)
** @return: nova string concatenada ou NULL se erro
*/
char	*append_str(char *s1, const char *s2)
{
	char	*result;

	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

/*
** Atualiza o estado de aspas do expander
** @param exp: estrutura do expander
** @param c: caractere atual
*/
void	update_quote_state(t_expander *exp, char c)
{
	if (exp->state == STATE_NORMAL)
	{
		if (c == '\'')
			exp->state = STATE_SINGLE;
		else if (c == '"')
			exp->state = STATE_DOUBLE;
	}
	else if (exp->state == STATE_SINGLE && c == '\'')
		exp->state = STATE_NORMAL;
	else if (exp->state == STATE_DOUBLE && c == '"')
		exp->state = STATE_NORMAL;
}
