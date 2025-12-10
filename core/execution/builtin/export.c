/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:02:41 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/10 16:02:00 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_env *env, char *args)
{
	t_env	*head;

	head = env;
	if (!args)
	{
		export_with_no_arguments(head);
		return ;
	}
	
}

void	export_with_no_arguments(t_env *head)
{
	while (head != NULL)
	{
		write(1, "declare -x", 10);
		print_all_env(head);
		head = head->next;
	}
}