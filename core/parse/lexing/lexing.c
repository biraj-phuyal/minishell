/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:22:16 by gude-and          #+#    #+#             */
/*   Updated: 2025/11/22 21:40:21 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/*
A função tokenize recebe uma string line e devolve uma lista ligada de t_token, começando no índice 0, contendo todos os tokens encontrados na ordem.
No final, ela adiciona um token END.
Em caso de erro grave de lexing (por exemplo, aspas não fechadas), ela não devolve lista válida (por exemplo, retorna NULL e libera o que já criou).
*/

t_token tokenize(char *line)
{
    int i = 0;
    int idx = 0;

    t_token *head = NULL;
    t_token *tail = head;

    while(line[i])
    {
        if(line[i] == '\t' || line[i] == ' ')
            i++;
        else if(lex_pipe(line[i],idx++, *head))
        i++;
        else if ()...
    }
    
    
}


int lex_pipe(char c, int idx, t_token token)
{
    if(c == '|')
    {
        token.type = PIPE;
        token.idx = idx;
        return 1;
    }
    return 0;
}