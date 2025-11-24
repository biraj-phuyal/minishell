/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:32:47 by biphuyal          #+#    #+#             */
/*   Updated: 2025/11/24 21:17:21 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;

char	*get_key(char *envp);
char	*get_value(char *envp);
t_env	init_env(char **environ);
bool	repeated(t_env *env, char *key);
void	free_list(t_env *env, char *message);
t_env	*create_list(t_env *env, char *envp);
char	*destroy_and_copy(char *dest, char *src);

#endif