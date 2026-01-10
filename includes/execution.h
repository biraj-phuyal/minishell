/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:32:47 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/10 23:06:14 by biphuyal         ###   ########.fr       */
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

typedef struct s_exec_ctx
{
	t_env	**env;
	char	**envp;
	int		(*pipes)[2];
	int		pipe_count;
	t_cmd	**cmds;
	pid_t	*pids;
	int		cmd_count;
	void	*ast;
}	t_exec_ctx;

typedef struct s_pipe_run
{
	t_cmd	**cmds;
	pid_t	*pids;
	int		count;
}	t_pipe_run;

char		*get_pwd(void);
bool		flag(char *argv);
void		echo(t_cmd *cmd);
void		free_env(t_env *env);
void		order_env(char **env);
void		print_pwd(t_env *env);
void		free_hd(t_heredoc *hd);
t_env		*init_env(char **envp);
char		*get_new_dir(t_cmd *cmd);
void		exit_program(t_env *env);
int			exit_builtin(t_cmd *cmd, t_env *env);
void		print_all_env(t_env *env);
char		*get_key(const char *envp);
void		update_new_pwd(t_env *env);
void		create_new_pwd(t_env *env);
char		*read_pipe_content(int fd);
t_env		*free_head_node(t_env *env);
int			get_exit_status(int status);
char		*path(t_env *env, char *cmd);
char		*get_value(const char *envp);
bool		is_builtin(t_cmd *cmd, int i);
int			apply_dup2_close(int fd, int target);
t_env		*unset(t_env *env, char *key);
void		handle_heredoc_sigint(int sig);
int			export(t_env *env, char *args);
void		free_list_and_exit(t_env *env);
bool		repeated(t_env *env, char *key);
int			pipe_cmd_count(t_ast_node *ast);
size_t		strlen_double_array(char **env);
void		free_double_pointer(char **envp);
void		close_all_pipes(t_exec_ctx *ctx);
int			create_all_pipes(t_exec_ctx *ctx);
char		**list_to_array(const t_env *env);
int			handle_output_redir(t_redir *curr);
void		new_pwd(t_env **env, char *old_pwd);
void		old_pwd(t_env **env, char *old_pwd);
void		push_back(t_env **head, t_env *new);
int			setup_redirections(t_redir *redirs);
char		*return_value(t_env *env, char *key);
int			handle_heredoc_redir(t_redir *redir);
int			full_length_of_list(const t_env *env);
int			change_dir(t_env **env, char *new_dir);
void		update_old_pwd(t_env *env, char *og_pwd);
void		create_old_pwd(t_env *env, char *og_pwd);
int			execute_cd(t_cmd *cmd, int i, t_env **env);
void		destroy_and_copy(char **dest, const char *src);
int			execute_builtin(t_cmd *cmd, int i, t_env **env);
int			execute_builtin(t_cmd *cmd, int i, t_env **env);
void		close_cmd_fds(int saved_stdin, int saved_stdout);
int			execute(t_ast_node *ast, t_env **env, char **envp);
char		*join_key_value(const char *key, const char *value);
void		move_back(t_env **env, char *old_pwd, char *new_dir);
void		get_fds(t_exec_ctx *ctx, int i, int count, int fd[2]);
int			handle_errors(char *line, t_heredoc *hd, int pipe_fd);
int			pipe_fill_cmds(t_ast_node *ast, t_cmd **cmds, int count);
void		set_value(t_env **env, const char *key, const char *value);
int			execute_pipeline(t_ast_node *ast, t_env **env, char **envp);
void		move_to_previous_dir(t_env **env, char *old_pwd, char *new_dir);
void		move_to_relative_path(t_env **env, char *old_pwd, char *new_dir);
void		child_exec_cmd(t_cmd *cmd, t_exec_ctx *ctx);
void		child_dup(int in_fd, int out_fd);
void		child_cleanup(t_exec_ctx *ctx);

#endif