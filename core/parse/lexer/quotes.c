/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:56:10 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/10 21:54:24 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

/*
** Verifica se o caractere é uma aspa (simples ou dupla)
*/
bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

/*
** Encontra a posição da aspa de fechamento correspondente
** @param str: string a ser analisada
** @param pos: posição da aspa de abertura
** @return: posição após a aspa de fechamento, ou pos+1 se não encontrar
*/
static size_t	find_closing_quote(const char *str, size_t pos)
{
	char	quote_char;
	size_t	i;

	quote_char = str[pos];
	i = pos + 1;
	while (str[i])
	{
		if (str[i] == quote_char)
			return (i + 1);
		i++;
	}
	return (pos + 1);
}

/*
** Verifica se todas as aspas a partir de uma posição estão fechadas
** @param str: string a ser verificada
** @param start: posição inicial
** @return: true se todas as aspas estão fechadas, false caso contrário
*/
bool	quotes_are_closed(const char *str, size_t start)
{
	size_t	i;
	char	quote_char;

	i = start;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			quote_char = str[i];
			i++;
			while (str[i] && str[i] != quote_char)
				i++;
			if (! str[i])
				return (false);
		}
		i++;
	}
	return (true);
}

/*
** Pula uma seção entre aspas
** @param str: string de entrada
** @param pos: posição da aspa de abertura
** @return: posição após a aspa de fechamento
*/
size_t	skip_quoted_section(const char *str, size_t pos)
{
	if (! str || ! is_quote(str[pos]))
		return (pos + 1);
	return (find_closing_quote(str, pos));
}

/*
** Extrai o conteúdo de uma seção entre aspas (incluindo as aspas)
** Útil para processamento posterior (expansão de variáveis)
** @param str: string de entrada
** @param pos: ponteiro para a posição atual (será atualizado)
** @return: substring alocada contendo o conteúdo com aspas
*/
char	*extract_quoted_content(const char *str, size_t *pos)
{
	size_t	start;
	size_t	end;
	char	*content;

	if (!str || !pos || !is_quote(str[*pos]))
		return (NULL);
	start = *pos;
	end = skip_quoted_section(str, start);
	content = ft_substr(str, start, end - start);
	*pos = end;
	return (content);
}
