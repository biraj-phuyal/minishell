/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:41:38 by biphuyal          #+#    #+#             */
/*   Updated: 2025/11/24 21:15:12 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

void	overwrite(t_env *env, char *key, char *value)
{
	t_env	*head;

	head = env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, key) == 0)
			head->value = destroy_and_copy(head->value, value);
		if (!head->value)
			free_exit(head, "Allocation failure");
		head = head->next;
	}
}

char	*destroy_and_copy(char *dest, char *src)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(ft_strlen(src) + 1);
	if (!new)
		return (NULL);
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (free(dest), new);
}
