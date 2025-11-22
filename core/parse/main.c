/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:07:16 by gude-and          #+#    #+#             */
/*   Updated: 2025/11/22 20:53:51 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int	main(int argc, char **argv, char **env)
{
    (void)argc; (void)argv; (void)env;
    
    while(1)
    {
        char *line = readline("./minishell");
        if(line == NULL)
        {
            printf("exit\n");
            return 0;
        }
        if(emptyline(line))
        {
            free(line);
            continue;
        }
        add_history(line);
        t_token *tokens = tokenize(line);
        free(line);
        if(tokens == NULL)
            continue;
        free_tokens(tokens);
    }
    return 0;
}