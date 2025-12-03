/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 01:59:17 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/03 18:46:34 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

char	**list_to_array(t_env *env)
{
	char	**envp;
	t_env	*head;
	int		total_length;
	int		i;

	total_length = full_length_of_list(env);
	envp = (char **)malloc((total_length + 1 ) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	head = env;
	while (i < total_length && head != NULL)
	{
		envp[i] = append_string(head->key, head->value);
		if (!envp[i])
			free_exit(env, "Allocation Failure");
		i++;
		head = head->next;
	}
	envp[i] = NULL;
	return (envp);
}