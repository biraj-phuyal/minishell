/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:47:34 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/12 15:58:41 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <strings.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
#include <stdint.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "execution.h"

void		ft_putstr(char *s);
size_t		ft_strlen(const char *s);
char		*ft_strdup(char *s);
void		ft_bzero(void *s, size_t n);
int			ft_strcmp(char *s1, char *s2);
void		ft_strcpy(char *dest, char *src);
char		*ft_strchr(const char *s, int c);
void		*ft_calloc(size_t count, size_t size);
char		*ft_substr(char *s, unsigned int start, ssize_t len);

#endif