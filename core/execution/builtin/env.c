/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:16:51 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/13 17:46:52 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_all_env(t_env *env)
{
	t_env	*head;
	
	head = env;
	while(head != NULL)
	{
		ft_putstr(head->key);
		write(1, "=", 1);
		if (head->value)
			ft_putstr(head->value);
		write(1, "\n", 1);
		head = head->next;
	}
}