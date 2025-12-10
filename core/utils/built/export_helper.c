/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:51:12 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/10 18:42:50 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **format_env(char **env)
{
    int     len;
    int     swapped;

	len = strlen_double_array(env);
	if (len <= 1)
		return (env);
    swapped = 1;
    while (swapped)
    {
        swapped = 0;
		format_helper(env, &swapped, len);
    }
    return (env);
}

void	format_helper(char **env, int *swapped, int len)
{
	int		i;
    char    *tmp;
	char    *key1;
    char    *key2;

	i = 0;
	while (i < len - 1)
	{
		key1 = get_key(env[i]);
		key2 = get_key(env[i + 1]);

		if (ft_strcmp(key1, key2) > 0)
		{
			tmp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = tmp;
			*swapped = 1;
		}
		free(key1);
		free(key2);
		i++;
	}
}
