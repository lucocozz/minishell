/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_binarie.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 17:01:28 by lucocozz          #+#    #+#             */
/*   Updated: 2021/09/06 17:04:41 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_binarie(char **argv)
{
	char	*bin_path;
	t_env	*env;

	env = get_shell_env();
	if (ft_strstr(argv[0], "./") != NULL)
	{
		bin_path = get_real_filepath(argv[0]);
		if (bin_path == NULL)
			return (-1);
	}
	else
		bin_path = getbinpath(argv[0]);
	if (bin_path == NULL)
		return (-1);
	if (execve(bin_path, argv, *env) == -1)
	{
		gc_free((void **)&bin_path);
		return (-1);
	}
	gc_free((void **)&bin_path);
	return (0);
}
