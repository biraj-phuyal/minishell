/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:47:34 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/04 18:18:55 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <lexer.h>
# include <utils.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdint.h>
# include <parser.h>
# include <strings.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <expander.h>
# include <sys/types.h>
# include <execution.h>
# include <readline/readline.h>
# include <readline/history.h>

void	program_loop(t_env *env);
void	handle_sigint(int sig);
void	handle_sigint_heredoc(int sig);

#endif