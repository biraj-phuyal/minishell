/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:04:26 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/04 16:58:01 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

t_env	*free_head_node(t_env *env)
{
	t_env	*first;

	if (!env)
		return (NULL);
	first = env->next;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
	return (first);
}
