/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:32:47 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/12 19:34:28 by biphuyal         ###   ########.fr       */
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
	struct s_env	*next;
}	t_env;

char	*get_pwd(void);
char	*get_key(const char *envp);
void	free_list(t_env *env);
void	print_pwd(t_env *env);
char	*get_value(char *envp);
t_env	*init_env(char **envp);
void	print_all_env(t_env *env);
t_env	*update_new_pwd(t_env *env);
t_env	*create_new_pwd(t_env *env);
t_env	*free_head_node(t_env *env);
char	**list_to_array(const t_env *env);
void	free_envp(char **envp, int i);
bool	repeated(t_env *env, char *key);
int		full_length_of_list(const t_env *env);
t_env	*new_pwd(t_env *env, char *old_pwd);
t_env	*old_pwd(t_env *env, char *old_pwd);
void	push_back(t_env **head, t_env *new);
void	move_back(t_env *env, char *old_pwd);
char	*return_value(t_env *env, char *key);
char	*join_key_value(const char *key, const char *value);
void	destroy_and_copy(char **dest, const char *src);
t_env	*update_old_pwd(t_env *env, char *og_pwd);
t_env	*create_old_pwd(t_env *env, char *og_pwd);
void	move_to_previous_dir(t_env *env, char *old_pwd);
void	export_if_arguments(t_env **env, const char *args);
void	set_value(t_env **env, const char *key, const char *value);
void	move_to_relative_path(t_env *env, char *old_pwd, char *new_dir);
void	order_env(char **env);

#endif