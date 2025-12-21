/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:30:00 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/21 20:44:34 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

char	*extract_var_name(const char *str, size_t *len)
{
	size_t	i;
	char	*name;

	if (!str || !len)
		return (NULL);
	i = 0;
	if (!is_var_char(str[i], true))
	{
		*len = 0;
		return (NULL);
	}
	while (str[i] && is_var_char(str[i], i == 0))
		i++;
	*len = i;
	name = ft_substr(str, 0, i);
	return (name);
}

char	*get_env_value(const char *name, char **env)
{
	size_t	i;
	size_t	name_len;
	char	*value;

	if (!name || !env)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0
			&& env[i][name_len] == '=')
		{
			value = ft_strdup(env[i] + name_len + 1);
			return (value);
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*expand_variable(t_expander *exp)
{
	size_t	var_len;
	char	*var_name;
	char	*value;

	if (exp->input[exp->pos] == '?')
	{
		exp->pos++;
		return (ft_itoa(exp->exit_status));
	}
	var_name = extract_var_name(exp->input + exp->pos, &var_len);
	if (!var_name || var_len == 0)
	{
		if (var_name)
			free(var_name);
		return (ft_strdup("$"));
	}
	exp->pos += var_len;
	value = get_env_value(var_name, exp->env);
	free(var_name);
	return (value);
}
