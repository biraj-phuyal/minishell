/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:16:51 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/10 14:34:40 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_all_env(t_env *env)
{
	t_env	*head;
	
	head = env;
	while(head != NULL)
	{
		print_env(head, head->key, head->value);
		head = head->next;
	}
}
void	print_env(t_env *head, char *key, char *value)
{
	if (head->exported == 0)
	{
		ft_putstr(head->key);
		write(1, "=", 1);
		ft_putstr(head->value);
	}
}