/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:21:51 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/10 23:06:14 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	parse_exit_code(const char *str)
{
	long long	num;
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	num = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	num = num * sign;
	return ((unsigned char)(num % 256));
}

void	exit_program(t_env *env)
{
	free_env(env);
	rl_clear_history();
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

int	exit_builtin(t_cmd *cmd, t_env *env)
{
	int	exit_code;

	printf("exit\n");
	if (cmd->argc == 1)
	{
		free_env(env);
		rl_clear_history();
		exit(0);
	}
	if (!is_numeric(cmd->argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		free_env(env);
		rl_clear_history();
		exit(2);
	}
	if (cmd->argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	exit_code = parse_exit_code(cmd->argv[1]);
	free_env(env);
	rl_clear_history();
	exit(exit_code);
	return (0);
}
