/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:32:47 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/09 00:07:50 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <strings.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;

char	*get_pwd(void);
char	*get_key(char *envp);
void	free_list(t_env *env);
char	*get_value(char *envp);
void	update_pwd(t_env *env);
t_env	*init_env(char **envp);
t_env	*update_new_pwd(t_env *env);
t_env	*free_head_node(t_env *env);
void	free_envp(char **envp, int i);
bool	repeated(t_env *env, char *key);
int		full_length_of_list(t_env *env);
t_env	*new_pwd(t_env *env, char *old_pwd);
t_env	*old_pwd(t_env *env, char *old_pwd);
char	*return_value(t_env *env, char *key);
char	*join_key_value(char *key, char *value);
char	*destroy_and_copy(char *dest, char *src);
t_env	*update_old_pwd(t_env *env, char *og_pwd);
void	help_double_dot(t_env *env, char *old_pwd);
t_env	*overwrite_value(t_env *env, char *key, char *value);
void	help_relative_path(t_env *env, char *old_pwd, char *new_dir);

#endif