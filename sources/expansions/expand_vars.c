/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:32:03 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/16 19:17:36 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_var_name_and_value(char *arg, char **var_name, char **var_value)
{
	if (*(arg + 1) == '?')
	{
		*var_name = ft_strdup("?");
		*var_value = ft_itoa(*get_exit_value());
	}
	else
	{
		*var_name = get_var_name(arg);
		*var_value = reverse_quotes(ft_getenv(*var_name));
		if (*var_value == NULL)
			*var_value = "";
	}
}

void	expand_vars_in_stream(char **arg)
{
	int		i;
	char	*var_name;
	char	*var_value;

	i = 0;
	while ((*arg)[i] != '\0')
	{
		if ((*arg)[i] == '$')
		{
			if ((*arg)[i] == '\0' ||
					(ft_isalnum((*arg)[i + 1]) == 0 && (*arg)[i + 1] != '_'))
				*arg = fill_new_arg(arg, 0, i++, "$");
			else
			{
				get_var_name_and_value(*arg + i, &var_name, &var_value);
				*arg = fill_new_arg(arg, ft_strlen(var_name), i, var_value);
				i += ft_strlen(var_value);
				gc_free((void **)&var_name);
				if (*var_value != '\0')
					gc_free((void **)&var_value);
			}
		}
		else
			++i;
	}
}

bool	expand_single_var(
		t_simple_cmd *cmd, int const i, int *j, bool in_dquotes)
{
	char	*var_name;
	char	*var_value;

	get_var_name_and_value(&cmd->argv[i][*j], &var_name, &var_value);
	if (in_dquotes == false && var_value != NULL && *var_value != '\0'
		&& has_space(var_value) == true)
	{
		if (realloc_argv(cmd, i, j, var_value) == false)
		{
			gc_free((void **)&var_name);
			if (*var_value != '\0')
				gc_free((void **)&var_value);
			return (false);
		}
	}
	else
	{
		cmd->argv[i]
			= fill_new_arg(&cmd->argv[i], ft_strlen(var_name), *j, var_value);
		*j += ft_strlen(var_value);
	}
	gc_free((void **)&var_name);
	if (*var_value != '\0')
		gc_free((void **)&var_value);
	return (true);
}

static bool	check_next_char(char c)
{
	return (c == '\0' || ((ft_isalnum(c) == 0 && c != '_') && c != '?'));
}

bool	expand_vars(t_simple_cmd *cmd, int const i)
{
	int		j;
	bool	in_squotes;
	bool	in_dquotes;

	j = 0;
	in_squotes = false;
	in_dquotes = false;
	while (cmd->argv[i] != NULL && cmd->argv[i][j] != '\0')
	{
		if (cmd->argv[i][j] == '$' && in_squotes == false)
		{
			if (check_next_char(cmd->argv[i][j + 1]) == true)
				cmd->argv[i] = fill_new_arg(&cmd->argv[i], 0, j++, "$");
			else
				if (expand_single_var(cmd, i, &j, in_dquotes) == false)
					return (false);
		}
		else
		{
			change_quote_state(cmd->argv[i][j], &in_squotes, &in_dquotes);
			++j;
		}
	}
	return (true);
}
