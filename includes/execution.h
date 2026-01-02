/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:32:47 by biphuyal          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/01/03 10:14:48 by biphuyal         ###   ########.fr       */
=======
/*   Updated: 2026/01/02 15:28:08 by biphuyal         ###   ########.fr       */
>>>>>>> 0688264 (path joining for execve is working)
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
bool		flag(char *argv);
void		echo(t_cmd *cmd);
void		free_env(t_env *env);
void		order_env(char **env);
void		print_pwd(t_env *env);
t_env		*init_env(char **envp);
char		*get_new_dir(t_cmd *cmd);
void		exit_program(t_env *env);
void		print_all_env(t_env *env);
char		*get_key(const char *envp);
void		update_new_pwd(t_env *env);
void		create_new_pwd(t_env *env);
t_env		*free_head_node(t_env *env);
char		*path(t_env *env, char *cmd);
char		*get_value(const char *envp);
bool		is_builtin(t_cmd *cmd, int i);
t_env		*unset(t_env *env, char *key);
void		export(t_env *env, char *args);
void		free_list_and_exit(t_env *env);
bool		repeated(t_env *env, char *key);
size_t		strlen_double_array(char **env);
void		free_double_pointer(char **envp);
char		**list_to_array(const t_env *env);
void		new_pwd(t_env **env, char *old_pwd);
void		old_pwd(t_env **env, char *old_pwd);
void		push_back(t_env **head, t_env *new);
char		*return_value(t_env *env, char *key);
int			full_length_of_list(const t_env *env);
void		change_dir(t_env **env, char *new_dir);
void		update_old_pwd(t_env *env, char *og_pwd);
void		create_old_pwd(t_env *env, char *og_pwd);
void		execute_cd(t_cmd *cmd, int i, t_env **env);
void		destroy_and_copy(char **dest, const char *src);
int			execute_builtin(t_cmd *cmd, int i, t_env **env);
int			execute_builtin(t_cmd *cmd, int i, t_env **env);
int			execute(t_ast_node *ast, t_env **env, char **envp);
char		*join_key_value(const char *key, const char *value);
void		move_back(t_env **env, char *old_pwd, char *new_dir);
void		set_value(t_env **env, const char *key, const char *value);
void		move_to_previous_dir(t_env **env, char *old_pwd, char *new_dir);
void		move_to_relative_path(t_env **env, char *old_pwd, char *new_dir);
int			execute_external_command(char *cmd_path, t_cmd *cmd, char **envp);
int			multiple_command_helper(t_ast_node *node, t_env *env, char **envp);

#endif