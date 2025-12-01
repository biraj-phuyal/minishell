/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 01:59:17 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/01 17:11:20 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

char	**list_to_array(t_env *env)
{
	char	**envp;
	int		total_length;

	total_length = full_length_of_list(env);
	envp = (char **)malloc((total_length + 1 ) * sizeof(char *));
	if (!envp)
		return (NULL);
}