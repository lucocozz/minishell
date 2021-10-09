/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 00:45:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/09 17:50:03 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* bool	expand_wildcard_in_stream(char **arg) */
/* { */
	/* char	**wildcard_array; */

	/* if (check_for_unquoted_char('*', *arg) == true) */
	/* { */
		/* wildcard_array = wildcard(*arg); */
		/* if (wildcard_array != NULL) */
		/* { */
			/* if (get_len_array(wildcard_array) != 1) */
			/* { */
				/* ft_dprintf(STDERR_FILENO, */
					/* "minishell: %s: ambiguous redirect\n", *arg); */
				/* return (false); */
			/* } */
			/* else */
			/* { */
				/* *arg = ft_strdup(*wildcard_array); */
				/* free_array(&wildcard_array); */
				/* gc_free((void **)&wildcard_array); */
			/* } */
		/* } */
	/* } */
	/* return (true); */
/* } */

static char	**add_wildcard_to_argv(
		char **argv, char **wildcard, int index_to_replace)
{
	char	**new_argv;
	int		len_new_argv;
	int		i_old;
	int		i_new;

	len_new_argv = get_len_array(argv) + get_len_array(wildcard);
	new_argv = gc_malloc(sizeof(*new_argv) * len_new_argv);
	i_old = 0;
	i_new = 0;
	while (i_old < index_to_replace)
		new_argv[i_new++] = ft_strdup(argv[i_old++]);
	while (*wildcard != NULL)
		new_argv[i_new++] = ft_strdup(*wildcard++);
	++i_old;
	while (argv[i_old] != NULL)
		new_argv[i_new++] = ft_strdup(argv[i_old++]);
	new_argv[i_new] = NULL;
	return (new_argv);
}

bool	expand_wildcard(t_simple_cmd *cmd)
{
	int		i;
	char	**tmp;
	char	**wildcard_array;

	i = 0;
	while (cmd->argv[i] != NULL)
	{
		if (check_for_unquoted_char('*', cmd->argv[i]) == true)
		{
			wildcard_array = wildcard(cmd->argv[i]);
			if (check_if_expansion_is_valid(i, &wildcard_array, cmd->argv)
				== false)
				return (false);
			if (wildcard_array != NULL)
			{
				tmp = add_wildcard_to_argv(cmd->argv, wildcard_array, i);
				free_array(&wildcard_array);
				gc_free((void **)&wildcard_array);
				cmd->argv = tmp;
			}
		}
		++i;
	}
	return (true);
}
