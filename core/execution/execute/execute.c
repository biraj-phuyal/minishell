/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:09:11 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/04 21:56:07 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pipe_cmd_count(t_ast_node *ast)
{
	int	count;

	if (!ast)
		return (0);
	count = 1;
	while (ast && ast->type == NODE_PIPE)
	{
		count++;
		ast = ast->left;
	}
	return (count);
}

int	pipe_fill_cmds(t_ast_node *ast, t_cmd **cmds, int count)
{
	int	i;

	if (!ast || !cmds || count <= 0)
		return (0);
	i = count - 1;
	while (ast && ast->type == NODE_PIPE && i > 0)
	{
		cmds[i] = ast->right->cmd;
		i--;
		ast = ast->left;
	}
	if (!ast || ast->type != NODE_CMD)
		return (0);
	cmds[0] = ast->cmd;
	return (1);
}
int	setup_redirections(t_redir *redirs)
{
    t_redir	*curr;
    int		fd;

    curr = redirs;
    while (curr)
    {
        if (curr->type == REDIR_IN)
        {
            fd = open(curr->file, O_RDONLY);
            if (fd == -1)
                return (perror(curr->file), -1);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (curr->type == REDIR_OUT)
        {
            fd = open(curr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
                return (perror(curr->file), -1);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (curr->type == REDIR_APPEND)
        {
            fd = open(curr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
                return (perror(curr->file), -1);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (curr->type == REDIR_HEREDOC)
        {
            int pipe_fd[2];
            pipe(pipe_fd);
            write(pipe_fd[1], curr->heredoc_content, ft_strlen(curr->heredoc_content));
            close(pipe_fd[1]);
            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[0]);
        }
        curr = curr->next;
    }
    return (0);
}

int	execute_external_command(char *cmd_path, t_cmd *cmd, char **envp)
{
    pid_t	pid;
    int		status;

    pid = fork();
    if (pid == -1)
    {
        free(cmd_path);
        return (1);
    }
    if (pid == 0)
    {
        if (setup_redirections(cmd->redirs) == -1)
            exit(1);
        execve(cmd_path, cmd->argv, envp);
        perror("minishell");
        free(cmd_path);
        exit(126);
    }
    free(cmd_path);
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (1);
}

int	execute_one_command(t_cmd *cmd, t_env **env, char **envp)
{
    char	*cmd_path;
    int		saved_stdin;
    int		saved_stdout;
    int		ret;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (0);
    if (is_builtin(cmd, 0))
    {
        saved_stdin = dup(STDIN_FILENO);
        saved_stdout = dup(STDOUT_FILENO);
        if (setup_redirections(cmd->redirs) == -1)
        {
            dup2(saved_stdin, STDIN_FILENO);
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdin);
            close(saved_stdout);
            return (1);
        }
        ret = execute_builtin(cmd, 0, env);
        dup2(saved_stdin, STDIN_FILENO);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdin);
        close(saved_stdout);
        return (ret);
    }
    cmd_path = path(*env, cmd->argv[0]);
    if (!cmd_path)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd->argv[0], 2);
        ft_putendl_fd(": command not found", 2);
        return (127);
    }
    return (execute_external_command(cmd_path, cmd, envp));
}

int	execute(t_ast_node *ast, t_env **env, char **envp)
{
	if (ast->type == NODE_CMD)
		return (execute_one_command(ast->cmd, env, envp));
	if (ast->type == NODE_PIPE)
		return (execute_pipeline(ast, env, envp));
	return (0);
}
