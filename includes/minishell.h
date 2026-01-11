/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:47:34 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/11 20:16:09 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <lexer.h>
# include <utils.h>
# include <errno.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdint.h>
# include <parser.h>
# include <strings.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <expander.h>
# include <sys/types.h>
# include <execution.h>

# define SIG_NORMAL 0
# define SIG_INTERRUPT_HEREDOC 2
# include <readline/readline.h>
# include <readline/history.h>

void	setup_signals(void);
void	ignore_signals(void);
void	restore_signals(void);
void	default_signals(void);
void	handle_sigint(int sig);
void	program_loop(t_env *env);

#endif