/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emptyline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:56:39 by gude-and          #+#    #+#             */
/*   Updated: 2025/11/22 21:22:38 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int emptyline(const char *line)
{
    if(line[0] == '\0')
        return 1;
    int i  = 0;
    while(line[i])
    {
        if(line[i] != ' ' && line[i] != '\t')
            return 0;
        i++;
    }
    return 1;
}