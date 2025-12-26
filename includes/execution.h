/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:32:47 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/26 17:45:19 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <minishell.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

char		*get_pwd(void);
void		free_env(t_env *env);
void		order_env(char **env);
void		print_pwd(t_env *env);
t_env		*init_env(char **envp);
void		free_envp(char **envp);
char		*get_new_dir(t_cmd *cmd);
void		exit_program(t_env *env);
void		print_all_env(t_env *env);
char		*get_key(const char *envp);
void		update_new_pwd(t_env *env);
void		create_new_pwd(t_env *env);
t_env		*free_head_node(t_env *env);
char		*get_value(const char *envp);
bool		is_builtin(t_cmd *cmd, int i);
void		free_list_and_exit(t_env *env);
bool		repeated(t_env *env, char *key);
size_t		strlen_double_array(char **env);
char		**list_to_array(const t_env *env);
void		new_pwd(t_env **env, char *old_pwd);
void		old_pwd(t_env **env, char *old_pwd);
void		push_back(t_env **head, t_env *new);
void		export(t_env *env, const char *args);
char		*return_value(t_env *env, char *key);
int			full_length_of_list(const t_env *env);
void		change_dir(t_env **env, char *new_dir);
void		update_old_pwd(t_env *env, char *og_pwd);
void		create_old_pwd(t_env *env, char *og_pwd);
void		execute_cd(t_cmd *cmd, int i, t_env **env);
void		destroy_and_copy(char **dest, const char *src);
int			execute_builtin(t_cmd *cmd, int i, t_env **env);
int			execute(t_ast_node *ast, t_env **env, char **envp);
char		*join_key_value(const char *key, const char *value);
void		move_back(t_env **env, char *old_pwd, char *new_dir);
void		set_value(t_env **env, const char *key, const char *value);
void		move_to_previous_dir(t_env **env, char *old_pwd, char *new_dir);
void		move_to_relative_path(t_env **env, char *old_pwd, char *new_dir);

#endif