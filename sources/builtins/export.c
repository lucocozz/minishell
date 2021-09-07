/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:44:08 by lucocozz          #+#    #+#             */
/*   Updated: 2021/09/07 23:52:25 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	display_env(void)
{
	int		i;
	t_env	*env;
	int		index_equalsign;

	i = 0;
	env = get_shell_env();
	while ((*env)[i])
	{
		if (ft_strchr((*env)[i], '=') != NULL)
		{
			ft_putstr("export ");
			index_equalsign = ft_strchr((*env)[i], '=') - (*env)[i];
			write(STDOUT_FILENO, (*env)[i], index_equalsign);
			if ((*env)[i][index_equalsign + 1] != '\0')
				ft_printf("=\"%s\"\n", (*env)[i] + index_equalsign + 1);
			else
				ft_putchar('\n');
		}
		i++;
	}
	return (0);
}

static int	get_len_var_name(char *arg)
{
	int	len;

	len = 0;
	while (arg[len] != '+' && arg[len] != '=' && arg[len] != '\0')
			++len;
	return (len);
}

static char	*get_var_name(char	*arg)
{
	int		i;
	int		j;
	char	*var_name;

	i = 0;
	j = 0;
	if (ft_isalpha(arg[i]) == 0)
		return (NULL);
	var_name = gc_malloc(sizeof(*var_name) * (get_len_var_name(arg) + 1));
	while (arg[i] != '+' && arg[i] != '=' && arg[i] != '\0')
	{
		if (ft_isalnum(arg[i]) == 0)
		{
			gc_free((void **)&var_name);
			return (NULL);
		}
		else
			var_name[j++] = arg[i];
		++i;
	}
	var_name[i] = '\0';
	if (arg[i] == '+' && arg[i + 1] != '=')
		gc_free((void **)&var_name);
	return (var_name);
}

int	export(int argc, char **argv)
{
	int		i;
	int		j;
	char	*var_name;
	char	*var_value;
	char	*ret_getenv;
	int		overwrite;

	if (argc <= 1)
		return (display_env());
	i = 1;
	while (argv[i] != NULL)
	{
		overwrite = 1;
		var_name = NULL;
		var_value = NULL;
		var_name = get_var_name(argv[i]);
		if (var_name == NULL)
		{
			ft_dprintf(STDOUT_FILENO,
				"minishell: export: `%s': not a valid identifier\n", argv[i]);
			return (EXIT_FAILURE);
		}
		j = 0;
		while (argv[i][j] != '=' && argv[i][j] != '\0')
			j++;
		if (argv[i][j] == '\0')
			var_value = NULL;
		else if (argv[i][j] == '=')
			var_value = "";
		else
			var_value = &(argv[i][++j]);
		ret_getenv = ft_getenv(var_name);
		if (argv[i][j - 2] == '+')
			var_value = ft_strjoin(ret_getenv, var_value, "");
		if (*var_value == '\0' && argv[i][j - 1] != '=')
			overwrite = 0;
		/* if (!(*var_value != '\0' && ret_getenv != NULL && *ret_getenv == '\0')) */
		ft_setenv(var_name, var_value, overwrite);
		gc_free((void **)&var_name);
		++i;
	}
	return (EXIT_SUCCESS);
}
