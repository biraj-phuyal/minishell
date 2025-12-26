/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:16:51 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/26 19:37:52 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_all_env(t_env *env)
{
	t_env	*head;

	head = env;
	while (head != NULL)
	{
		ft_putstr_fd(head->key, 1);
		write(1, "=", 1);
		ft_putstr_fd(head->value, 1);
		write(1, "\n", 1);
		head = head->next;
	}
}
