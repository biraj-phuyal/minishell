/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:02:41 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/10 23:06:14 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (false);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	export_with_arguments(t_env **env, const char *args)
{
	char	*key;
	char	*value;

	if (!is_valid_identifier(args))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd((char *)args, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	key = get_key(args);
	if (!key)
		return (0);
	value = get_value(args);
	if (!value)
	{
		free(key);
		return (0);
	}
	set_value(env, key, value);
	free(key);
	free(value);
	return (0);
}

void	export_with_no_arguments(const t_env *env)
{
	int		i;
	char	**array_env;

	array_env = list_to_array(env);
	if (!array_env)
		return ;
	order_env(array_env);
	i = 0;
	while (array_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr(array_env[i]);
		i++;
	}
}

int	export(t_env *env, char *args)
{
	if (!env)
		return (0);
	if (args)
		return (export_with_arguments(&env, args));
	export_with_no_arguments(env);
	return (0);
}
