/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:16:51 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/10 17:48:06 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_all_env(t_env *env)
{
	t_env	*head;
	
	head = env;
	while(head != NULL)
	{
		ft_putstr(env->key);
		write(1, "=", 1);
		ft_putstr(env->value);
		head = head->next;
	}
}