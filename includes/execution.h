/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:32:47 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/01 17:07:43 by biphuyal         ###   ########.fr       */
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
t_env	*init_env(char **envp);
char	*get_value(char *envp);
t_env	*free_head_node(t_env *env);
bool	repeated(t_env *env, char *key);
int		full_length_of_list(t_env *env);
void	free_exit(t_env *env, char *message);
t_env	*create_list(t_env *env, char *envp);
t_env	*get_first_node(char *key, char *value);
char	*destroy_and_copy(char *dest, char *src);
void	overwrite_value(t_env *env, char *key, char *value);

#endif